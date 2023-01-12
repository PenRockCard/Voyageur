//
// Created by Chris on 2023-01-12.
//

#include "People.h"

void People::AddPerson() {

    peopleList.push_back(new Person(GetNextID()));

}

/**
 *
 * @return The next id, and increments it.
 */
unsigned long long People::GetNextID() {

    return nextID++;

}

People::People() {
    nextID=0;
}
