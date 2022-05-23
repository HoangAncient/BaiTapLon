Obj me;
SDL_Renderer* ren_about_me=NULL;
bool running_about = true;
SDL_Window* win_me;
SDL_Event about_event;
void input_about() {
        while (SDL_PollEvent(&about_event)) {
                SDL_GetMouseState(&mousex,&mousey);
                if (about_event.type == SDL_QUIT) {
                        running_about = false;
                        SDL_DestroyRenderer(ren_about_me);
                        SDL_DestroyWindow(win_me);

                }
                if (about_event.type == SDL_KEYDOWN) {
                        if(about_event.key.keysym.sym == SDLK_ESCAPE) {
                                running_about = false;
                                SDL_DestroyRenderer(ren_about_me);
                                SDL_DestroyWindow(win_me);

                        }
                }
        }
}
void about_us(){
        running_about = true;
        SDL_CreateWindowAndRenderer(350,600,0,&win_me,&ren_about_me);

        //amir Pic
        me.setDest(0,0,350,600);
        me.setSource(0,0,1500,1500);
        me.setImage("data/he.jpg",ren_about_me);
        while (running_about) {

                SDL_RenderCopyEx(ren_about_me,me.tex,&me.src,&me.dest,0,NULL,SDL_FLIP_NONE);
                SDL_RenderPresent(ren_about_me);
                input_about();
        }
        status = 0;
}
