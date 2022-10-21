package com.example.sdlbase;

import org.libsdl.app.SDLActivity; 

public class SdlBase extends SDLActivity {
    @Override
    protected String[] getLibraries() {
        return new String[] {
            "main"
        };
    }    
}
