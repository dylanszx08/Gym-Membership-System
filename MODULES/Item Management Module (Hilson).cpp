#include <iostream>
using namespace std; 

void add_service();
void display_services();
void Micheal();

void display_services() {
	int choice;
	cout << "Welcome to the Gym Membership Services!" << endl;
	cout << "Please select a service from the following options:" << endl;
	cout << "1. Add Service" << endl;
	cout << "2. Remove Service" << endl;
	cout << "3. Update Service" << endl;
	cout << "4. Search Service" << endl;
	cout << "5. Display all services you own" << endl;
	cin >> choice;
	switch (choice) {
	case 1:
		
		add_service();
		break;
	case 2:
		cout << "You have selected remove service." << endl;
		break;
	case 3:
		cout << "You have selected update service." << endl;
		break;
	case 4:
		cout << "You have selected search service." << endl;
		break;
	case 5:
		cout << "You have selected display all service you own." << endl;
		break;
	default:
		cout << "Invalid choice. Please select a valid option." << endl;
		break;
	}
}
void add_service() {
	int addservicechoice, afteraddservice;

	cout << "You have selected to add a new service." << endl;
	//new service here
	cout << "Please select the type of service you would like to add:" << endl;
	cout << "1. Personal Training" << endl;
	cout << "2. Group Classes" << endl;
	cout << "3. Nutrition Counseling" << endl;
	cout << "4. Massage Therapy" << endl;
	cout << "5. Other" << endl;
	cin >> addservicechoice;
	if (addservicechoice == 1) {
		cout << "You have selected to add Personal Training." << endl;
		//add Personal Training here
		cout << "Please pick your trainer from the following list:" << endl;
		cout << "1. Micheal(male)" << endl;
		cout << "2. Jane(female)" << endl;
		cout << "3. Mike Tyson(male)" << endl;
		cout << "4. Selena Angie(female)" << endl;
		cin >> afteraddservice;
		switch (afteraddservice) {
		case 1:
			cout << "You have selected Micheal as your trainer." << endl;
			Micheal();
			break;

		case 2:
			cout << "You have selected Jane as your trainer." << endl;
			break;
		case 3:
			cout << "You have selected Mike Tyson as your trainer." << endl;
			break;
		case 4:
			cout << "You have selected Selena Angie as your trainer." << endl;
			break;
		default:
			cout << "Invalid choice. Please select a valid option." << endl;
			break;




		}

	}
}

void Micheal() {
	int timetable, fee, course, personality;

	cout << "You have selected Micheal as your trainer." << endl;
	cout << "Micheal's timetable is as follows:" << endl;
	cout << "Monday: 9am - 11am" << endl;
	cout << "Tuesday: 1pm - 3pm" << endl;
	cout << "Wednesday: 9am - 11am" << endl;
	cout << "Thursday: 1pm - 3pm" << endl;
	cout << "Friday: 9am - 11am" << endl;
	cout << "The fee for each session is 50$(per course),depending on how many course you have applied for." << endl;
	cout << "Micheal's course is as follows:" << endl;
	cout << "1. Weight Loss(best for overweight people)" << endl;
	cout << "2. Muscle Gain(best for gym lovers)" << endl;
	cout << "3. General Fitness(best for newbie)" << endl;
	cout << "Micheal's personality is a strict coach with great teaching skill and known as hardcore trainer for newbie " << endl;
	cout << "Please select the course you would like to take with Micheal:" << endl;
	cout << "1. Weight Loss" << endl;
	cout << "2. Muscle Gain" << endl;
	cout << "3. General Fitness" << endl;
	cin >> course;
	switch (course) {
	case 1:
		cout << "You have selected Weight Loss course with Micheal." << endl;
		break;
	case 2:
		cout << "You have selected Muscle Gain course with Micheal." << endl;
		break;
	case 3:
		cout << "You have selected General Fitness course with Micheal." << endl;
		break;
	default:
		cout << "Invalid choice. Please select a valid option." << endl;
		break;
	}

}




//void Jane() {
//void MikeTyson() {
//void SelenaAngie() {





























//void groupClasses() {
//void nutritionCounseling() {
//void massageTherapy() {
//void displayAllServices() { 
//void
//void
//void
//void
//void
//void
//void
//void
//void
//void
//void
//void


	int main() {
		display_services();
	



	return 0;
	}
