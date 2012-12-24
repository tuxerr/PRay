#include "renderer.hpp"

Renderer::Renderer(Scene *scene,Display *disp) : scene(scene), frameNumber(0) , display(disp)
{
    total_time=0;
}

void Renderer::set_scene(Scene *newscene) {
    scene=newscene;
}

std::vector<Color> Renderer::render(int x,int y,int width,int height,
                                    int thread_number,
                                    bool _onscreen) {
    onscreen=_onscreen;
    if(onscreen && display==NULL) {
        onscreen=false;
    }

    std::vector<Color> res;

    Uint32 initial_tick = SDL_GetTicks();

    if (onscreen) {

        int xx,yy;

#pragma omp parallel for private(xx,yy) schedule(dynamic,1) num_threads(thread_number)
        for (yy = y ; yy < height ; yy++) {
            for (xx = x ; xx < width ; xx++) {
                display->add_pixel(xx, yy, scene->renderPixel(xx, yy));
            }

// #pragma omp critical(refresh_display)
//             {
//                 display->refresh_part_display_timecheck();
//             }
        }

    } else {

        tasks.clear();
        results.clear();

#ifdef __GNUC__
        results.assign((width*height/PIXEL_GROUPS)+1,nullptr); // C++11
#else
        results.assign((width*height/PIXEL_GROUPS)+1,NULL);
#endif

        int i=0;
        Task currenttask;
        currenttask.task_number=0;

        std::vector<pthread_t> thread_pool;

        for(int h=0;h<height;h++) {

            for(int w=0;w<width;w++) {

                currenttask.pixels.push_back(std::pair<int,int>(x+w,y+h));
                if(i<(PIXEL_GROUPS-1)) {
                    i++;
                } else {
                    tasks.push_back(currenttask);
                    currenttask.pixels.clear();
                    currenttask.task_number++;
                    i=0;
                }
            }
        }

        for(i=0;i<thread_number;i++) {
            pthread_t thread;
            if(pthread_create(&thread,NULL,computing_thread,(void*)this)!=0) {
                Logger::log(LOG_ERROR)<<"Could not launch computing thread "<<i<<std::endl;
            }
            thread_pool.push_back(thread);
        }

        for(i=0;i<thread_number;i++) {
            pthread_join(thread_pool[i],NULL);
        }

        if(!onscreen) {
            for(unsigned int k=0;k<results.size();k++) {
                std::vector<Color>* taskres = results[k];
                if(taskres!=NULL) {
                    for(unsigned int j=0;j<taskres->size();j++) {
                        Color c = (*taskres)[j];
                        res.push_back(c);
                    }
                }
                delete taskres;
            }
        }

    }

    float render_time=(SDL_GetTicks()-initial_tick)/(float)1000;
    total_time+=render_time;

    Logger::log()<<"Frame "<< frameNumber++ <<" rendered in "
                 <<render_time
                 <<" seconds (total is "<<total_time<<" seconds)"<<std::endl;

    return res;
}

void* Renderer::computing_thread(void *This) {
    Renderer *rend_ptr = (Renderer*)This;
    rend_ptr->compute_task();
    return NULL;
}

void Renderer::compute_task() {
    bool cont=true;
    Task currenttask;
    while(cont) {
        bool compute=true;
        tasks_mut.lock();
        if(tasks.size()==0) {
            compute=false;
        } else {
            currenttask = tasks.back();
            tasks.erase(tasks.end()-1);
        }
        tasks_mut.unlock();

        if(compute) {
            if(!onscreen) {
                std::vector<Color> *res = new std::vector<Color>;
                for(unsigned int i=0;i<currenttask.pixels.size();i++) {
                    Color pixel = scene->renderPixel(currenttask.pixels[i].first,
                                                     currenttask.pixels[i].second);
                    res->push_back(pixel);
                }

                results_mut.lock();
                results[currenttask.task_number]=res;
                results_mut.unlock();
            } else {
                std::vector<Color> res;
                for(unsigned int i=0;i<currenttask.pixels.size();i++) {
                    Color pixel = scene->renderPixel(currenttask.pixels[i].first,
                                                     currenttask.pixels[i].second);
                    res.push_back(pixel);
                }
                results_mut.lock();
                display->add_line_group(currenttask.pixels[0].first,
                                        currenttask.pixels[0].second,res);
                display->refresh_part_display_timecheck();
                results_mut.unlock();
            }
        } else {
            cont=false;
        }

    }
}
