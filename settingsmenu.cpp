Obj background_sm, sound_sm,clearscore_sm, ball_sm;
int mousex_sm,mousey_sm;
SDL_Renderer* ren_sm;
bool smenu = true;
void input_sm() {
        while (SDL_PollEvent(&e)) {
                SDL_GetMouseState(&mousex_sm,&mousey_sm);
                if (e.type == SDL_QUIT) {
                        smenu = false;
                        windowloop = false;
                        SDL_Quit();
                        return;
                }
                if (e.type == SDL_KEYDOWN) {
                        if(e.key.keysym.sym == SDLK_ESCAPE) {
                                smenu = false;
                                windowloop = false;
                                SDL_Quit();
                                return;
                        }
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                        if ((mousex_sm>=sound_sm.dest.x)
                            &&(mousex_sm<=sound_sm.dest.x+sound_sm.dest.w)
                            &&(mousey_sm>=sound_sm.dest.y)
                            &&(mousey_sm<=sound_sm.dest.y+sound_sm.dest.h)) {
                                cout << "Audio Clicked" << endl;
                                bool musicstatus = checkaudio();
                                if(musicstatus) {
                                        stopaudio();
                                }else{
                                        startaudio();
                                }
                        }

                        if ((mousex_sm>=clearscore_sm.dest.x)
                            &&(mousex_sm<=clearscore_sm.dest.x+clearscore_sm.dest.w)
                            &&(mousey_sm>=clearscore_sm.dest.y)
                            &&(mousey_sm<=clearscore_sm.dest.y+clearscore_sm.dest.h)) {
                                cout << "Clear Highscore Clicked" << endl;
                                openfile(true);
                                cout<<"High score cleared"<<endl;
                        }
                        if ((mousex_sm>=ball_sm.dest.x)
                            &&(mousex_sm<=ball_sm.dest.x+ball_sm.dest.w)
                            &&(mousey_sm>=ball_sm.dest.y)
                            &&(mousey_sm<=ball_sm.dest.y+ball_sm.dest.h)) {
                                SDL_DestroyRenderer(ren_sm);
                                smenu = false;
                                status = 0;
                                return;

                        }

                }
        }
}
void settingsmenu(){
        smenu = true;
        ren_sm = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 350;
        rect.h = 600;
        // background_sm
        background_sm.setDest(0,0,350,600);
        background_sm.setSource(0,0,1200,1200);
        background_sm.setImage("data/background.jpg",ren_sm);
        // sound_sm
        sound_sm.setDest(150,100,70,70);
        sound_sm.setSource(0,0,1500,1500);
        sound_sm.setImage("data/sound.png",ren_sm);
        // clearscore_sm
        clearscore_sm.setDest(145,275,80,80);
        clearscore_sm.setSource(0,0,1500,1500);
        clearscore_sm.setImage("data/highscore_setting.png",ren_sm);
        // ball_sm
        ball_sm.setDest(150,475,70,70);
        ball_sm.setSource(0,0,1500,1500);
        ball_sm.setImage("data/back_icon.png",ren_sm);

        float hei = 0;
        bool down = true;
        float sh = 2.2;
        float pos = 0;
        float rot = 0;
        while (smenu) {
                int framecount = 0;
                int lastframe = SDL_GetTicks();
                static int lasttime = 0;
                if (lastframe >= lasttime+1000) {
                        lasttime = lastframe;
                        framecount = 0;
                }
                SDL_RenderCopyEx(ren_sm,background_sm.tex,&background_sm.src,&background_sm.dest,0,NULL,SDL_FLIP_NONE);
                SDL_RenderCopyEx(ren_sm,sound_sm.tex,&sound_sm.src,&sound_sm.dest,0,NULL,SDL_FLIP_NONE);
                SDL_RenderCopyEx(ren_sm,clearscore_sm.tex,&clearscore_sm.src,&clearscore_sm.dest,0,NULL,SDL_FLIP_NONE);
                SDL_RenderCopyEx(ren_sm,ball_sm.tex,&ball_sm.src,&ball_sm.dest,0,NULL,SDL_FLIP_NONE);
                rot += 2;

                pos = 10 + hei;
                if (down) {
                        if (pos >= 170) {
                                down = false;
                                hei -= sh;
                        } else {
                                hei += sh;
                        }
                } else {
                        if (pos <= 10) {
                                down = true;
                                hei += sh;
                        } else {
                                hei -= sh;
                        }
                }
                framecount++;
                int timerFPS = SDL_GetTicks() - lastframe;
                if (timerFPS < (1000/60)) {
                        SDL_Delay((1000/60)-timerFPS);
                }

                SDL_RenderPresent(ren_sm);
                input_sm();
        }
}
