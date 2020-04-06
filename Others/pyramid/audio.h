/*
* This file is part of elements project.
*
* Copyright (C) 2009-2011 William Oliveira de Lagos <william.lagos@icloud.com>
*
* Elements is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Elements is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with elements. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
//using namespace elements;

class Source {
public:
    void setLooping();
    void setSound(int);
    void setGain(float);
    void setAmbient();
    void play();
    void stop();
};

class Sample {
public:
    Sample(std::string);
    int get();
};

class Sound {
private:
    Source* source;
public:
    Sound(Source*);
    int loadStream(std::string);
    int playStream();
    void setEffects();
    Source* getSource();
};

class Audio {
private:
    Source *source;
    Sound *sound;
public:
    Audio();
};

#endif /* AUDIO_H */
