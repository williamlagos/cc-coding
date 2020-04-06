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

#include <audio.h>

void Source::setLooping()
{
  
}

void Source::setSound(int value)
{
  
}

void Source::setGain(float value)
{
  
}

void Source::setAmbient()
{
  
}

void Source::play()
{
  
}

void Source::stop()
{
  
}

Sample::Sample(std::string)
{
  
}

int Sample::get()
{
    return 0;
}

Sound::Sound(Source *src)
{
	source = src;
}

int Sound::loadStream(std::string fileName)
{
	try{
		source->stop();
		Sample *sample = new Sample(fileName);
		source->setSound(sample->get());
	}catch(std::exception e){
		std::cerr << e.what() << "\n";
		return -1;
	}
	return 0;
}
int Sound::playStream()
{
	try{
		source->play();
		source->stop();
	}catch(std::exception e){
		std::cerr << e.what() << "\n";
		return -1;
	}
	return 0;
}
void Sound::setEffects()
{
	source->setGain(0.6f); 
	source->setLooping();
	source->setAmbient();
}
Source* Sound::getSource()
{
	return source;
}
