//
// Created by Chris on 2023-01-12.
//

#include "People.h"

void People::AddPerson(unsigned long long PlanetID) {

    peopleList.push_back(new Person(GetNextID(),PlanetID));

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

vector<Person> People::getPeoplePlanet(unsigned long long planetID) {
    vector<Person> returnList;
    for (Person* elem:peopleList) {
        if (elem->GetPlanet()==planetID) {
            returnList.push_back(*elem);
        }
    }
    return returnList;
}

bool People::DeletePerson(unsigned long long personID) {
    unsigned long long location=findPersonID(personID);
//    if (location==NULL) {
//        return false;
//    }
    peopleList.erase(peopleList.begin()+location);
    cout << "Deleted Person ID: " << personID<< endl;
    return true;
}

/**
 * Returns the location of the person in the vector based on their ID.
 * @param personID
 * @return Person location in vector. If they aren't found, it returns null.
 */
unsigned long long People::findPersonID(unsigned long long personID) {

    unsigned long long location = 0;
    for (Person* elem:peopleList) {
        if (elem->GetID()==personID) {
            return location;
        }
        location++;
    }
    return NULL;
}

