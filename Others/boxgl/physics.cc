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

#include <physics.h>

Physics::Physics()
{
    /*b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    b2Body *groundBody,*body;
    b2BodyDef groundBodyDef,bodyDef;
    b2PolygonShape groundBox,dynamicBox;
    b2FixtureDef fixtureDef;*/
    timeStep = 1.0f / 60.0f;
    velocityIterations = 6;
    positionIterations = 2;
}

void Physics::initBOX2D(/*b2World* wrd*/)
{
	/*groundBodyDef.position.Set(0.0f, -10.0f);
	groundBody = world.CreateBody(&groundBodyDef);
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	body = world.CreateBody(&bodyDef);
	dynamicBox.SetAsBox(1.0f, 1.0f);

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	wrd = &world;*/
}
