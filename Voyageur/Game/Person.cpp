//
// Created by Chris on 2023-01-11.
//

#include "Person.h"

/**
 * Constructor
 * Currently all it does is assign them a random name
 * Hopefully more details will be added later
 */
Person::Person(unsigned long long newId, unsigned long long planetIDConstruct) {
//    auto nameArray = GetPeopleListTemp();
    planetID=planetIDConstruct;
    ID=newId;
    //Temporary solution to the GetPeopleListTemp not working
    string nameArray[] = {
            "James", "Mary",
            "Robert", "Patricia",
            "John", "Jennifer",
            "Michael", "Linda",
            "David", "Elizabeth",
            "William", "Barbara",
            "Richard", "Susan",
            "Joseph", "Jessica",
            "Thomas", "Sarah",
            "Charles", "Karen",
            "Christopher", "Lisa",
            "Daniel", "Nancy",
            "Matthew", "Betty",
            "Anthony", "Margaret",
            "Mark", "Sandra",
            "Donald", "Ashley",
            "Steven", "Kimberly",
            "Paul", "Emily",
            "Andrew", "Donna",
            "Joshua", "Michelle",
            "Kenneth", "Carol",
            "Kevin", "Amanda",
            "Brian", "Dorothy",
            "George", "Melissa",
            "Timothy", "Deborah",
            "Ronald", "Stephanie",
            "Edward", "Rebecca",
            "Jason", "Sharon",
            "Jeffrey", "Laura",
            "Ryan", "Cynthia",
            "Jacob", "Kathleen",
            "Gary", "Amy",
            "Nicholas", "Angela",
            "Eric", "Shirley",
            "Jonathan", "Anna",
            "Stephen", "Brenda",
            "Larry", "Pamela",
            "Justin", "Emma",
            "Scott", "Nicole",
            "Brandon", "Helen",
            "Benjamin", "Samantha",
            "Samuel", "Katherine",
            "Gregory", "Christine",
            "Alexander", "Debra",
            "Frank", "Rachel",
            "Patrick", "Carolyn",
            "Raymond", "Janet",
            "Jack", "Catherine",
            "Dennis", "Maria",
            "Jerry", "Heather",
            "Tyler", "Diane",
            "Aaron", "Ruth",
            "Jose", "Julie",
            "Adam", "Olivia",
            "Nathan", "Joyce",
            "Henry", "Virginia",
            "Douglas", "Victoria",
            "Zachary", "Kelly",
            "Peter", "Lauren",
            "Kyle", "Christina",
            "Ethan", "Joan",
            "Walter", "Evelyn",
            "Noah", "Judith",
            "Jeremy", "Megan",
            "Christian", "Andrea",
            "Keith", "Cheryl",
            "Roger", "Hannah",
            "Terry", "Jacqueline",
            "Gerald", "Martha",
            "Harold", "Gloria",
            "Sean", "Teresa",
            "Austin", "Ann",
            "Carl", "Sara",
            "Arthur", "Madison",
            "Lawrence", "Frances",
            "Dylan", "Kathryn",
            "Jesse", "Janice",
            "Jordan", "Jean",
            "Bryan", "Abigail",
            "Billy", "Alice",
            "Joe", "Julia",
            "Bruce", "Judy",
            "Gabriel", "Sophia",
            "Logan", "Grace",
            "Albert", "Denise",
            "Willie", "Amber",
            "Alan", "Doris",
            "Juan", "Marilyn",
            "Wayne", "Danielle",
            "Elijah", "Beverly",
            "Randy", "Isabella",
            "Roy", "Theresa",
            "Vincent", "Diana",
            "Ralph", "Natalie",
            "Eugene", "Brittany",
            "Russell", "Charlotte",
            "Bobby", "Marie",
            "Mason", "Kayla",
            "Philip", "Alexis",
            "Louis", "Lori"
    };

    int nameLocation = rand() % 100;
    name = nameArray[nameLocation];
}

/**
 *
 * @return the person's name
 */
string Person::GetName() {
    return name;
}

unsigned long long Person::GetPlanet() {
    return planetID;
}

/**
 * Temporary solution to return an array of people.
 * Not currently working.
 * @return
 */
string *Person::GetPeopleListTemp() {

    string nameArray[] = {
            "James", "Mary",
            "Robert", "Patricia",
            "John", "Jennifer",
            "Michael", "Linda",
            "David", "Elizabeth",
            "William", "Barbara",
            "Richard", "Susan",
            "Joseph", "Jessica",
            "Thomas", "Sarah",
            "Charles", "Karen",
            "Christopher", "Lisa",
            "Daniel", "Nancy",
            "Matthew", "Betty",
            "Anthony", "Margaret",
            "Mark", "Sandra",
            "Donald", "Ashley",
            "Steven", "Kimberly",
            "Paul", "Emily",
            "Andrew", "Donna",
            "Joshua", "Michelle",
            "Kenneth", "Carol",
            "Kevin", "Amanda",
            "Brian", "Dorothy",
            "George", "Melissa",
            "Timothy", "Deborah",
            "Ronald", "Stephanie",
            "Edward", "Rebecca",
            "Jason", "Sharon",
            "Jeffrey", "Laura",
            "Ryan", "Cynthia",
            "Jacob", "Kathleen",
            "Gary", "Amy",
            "Nicholas", "Angela",
            "Eric", "Shirley",
            "Jonathan", "Anna",
            "Stephen", "Brenda",
            "Larry", "Pamela",
            "Justin", "Emma",
            "Scott", "Nicole",
            "Brandon", "Helen",
            "Benjamin", "Samantha",
            "Samuel", "Katherine",
            "Gregory", "Christine",
            "Alexander", "Debra",
            "Frank", "Rachel",
            "Patrick", "Carolyn",
            "Raymond", "Janet",
            "Jack", "Catherine",
            "Dennis", "Maria",
            "Jerry", "Heather",
            "Tyler", "Diane",
            "Aaron", "Ruth",
            "Jose", "Julie",
            "Adam", "Olivia",
            "Nathan", "Joyce",
            "Henry", "Virginia",
            "Douglas", "Victoria",
            "Zachary", "Kelly",
            "Peter", "Lauren",
            "Kyle", "Christina",
            "Ethan", "Joan",
            "Walter", "Evelyn",
            "Noah", "Judith",
            "Jeremy", "Megan",
            "Christian", "Andrea",
            "Keith", "Cheryl",
            "Roger", "Hannah",
            "Terry", "Jacqueline",
            "Gerald", "Martha",
            "Harold", "Gloria",
            "Sean", "Teresa",
            "Austin", "Ann",
            "Carl", "Sara",
            "Arthur", "Madison",
            "Lawrence", "Frances",
            "Dylan", "Kathryn",
            "Jesse", "Janice",
            "Jordan", "Jean",
            "Bryan", "Abigail",
            "Billy", "Alice",
            "Joe", "Julia",
            "Bruce", "Judy",
            "Gabriel", "Sophia",
            "Logan", "Grace",
            "Albert", "Denise",
            "Willie", "Amber",
            "Alan", "Doris",
            "Juan", "Marilyn",
            "Wayne", "Danielle",
            "Elijah", "Beverly",
            "Randy", "Isabella",
            "Roy", "Theresa",
            "Vincent", "Diana",
            "Ralph", "Natalie",
            "Eugene", "Brittany",
            "Russell", "Charlotte",
            "Bobby", "Marie",
            "Mason", "Kayla",
            "Philip", "Alexis",
            "Louis", "Lori"
    };

    return nameArray;
}

unsigned long long int Person::GetID() {
    return ID;
}
