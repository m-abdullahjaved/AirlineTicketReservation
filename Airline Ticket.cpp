// M Abdullah Javed
// 03-134202-035
#include <iostream>
using namespace std;

struct Passengers {
	char Name[70];
	Passengers* next;
};

struct Flight {
	char flightName[70];
	Passengers* pHead;
	Flight* next;
};
Flight* fHead = NULL;

void addFlight();
void deleteFlight();
void manageFlight();
void displayFlight();
void displayPassengers(Flight*);
void reserveTicket(Flight*);
void cancelReservation(Flight* flight);

void addFlight() {
	Flight* temp = new Flight;
	char Name[70];
	cout << "Enter Flight Name : ";
	cin.getline(Name, 70);
	Flight* newNode = new Flight;
	strcpy_s(newNode->flightName, Name);
	newNode->pHead = NULL;
	if (fHead == NULL || strcmp(fHead->flightName, newNode->flightName) >= 0) {
		newNode->next = fHead;
		fHead = newNode;
	}
	else {
		temp = fHead;
		while (temp->next != NULL && strcmp(temp->next->flightName, newNode->flightName) < 0) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
}
void deleteFlight() {
	Flight* prevNode, * curNode;
	char Name[70];
	cout << "Enter Flight Name: ";
	cin.getline(Name, 70);
	prevNode = fHead;
	curNode = fHead->next;
	if (strcmp(prevNode->flightName, Name) == 0) {
		fHead = curNode;
		delete prevNode;
	}
	else {
		while (strcmp(curNode->flightName, Name) != 0) {
			curNode = curNode->next;
			prevNode = prevNode->next;
		}
		if (curNode == NULL) {
			prevNode->next = NULL;
			delete curNode;
		}
		else {
			prevNode->next = curNode->next;
			delete curNode;
		}
	}
}
void displayFlight() {
	Flight* temp = fHead;
	while (temp != NULL) {
		cout << temp->flightName << endl;
		temp = temp->next;
	}
	cout << endl;
}

void reserveTicket(Flight* flight) {
	Passengers* temp = new Passengers;
	char Name[70];
	cout << "Enter Person Name: ";
	cin.getline(Name, 70);
	Passengers* newNode = new Passengers;
	strcpy_s(newNode->Name, Name);
	if (flight->pHead == NULL || strcmp(flight->pHead->Name, newNode->Name) >= 0) {
		newNode->next = flight->pHead;
		flight->pHead = newNode;
	}
	else {
		temp = flight->pHead;
		while (temp->next != NULL && strcmp(temp->next->Name, newNode->Name) < 0) {
			temp = temp->next;
		}
		newNode->next = temp->next;
		temp->next = newNode;
	}
}

void cancelReservation(Flight* flight) {
	char Name[70];
	cout << "Enter Name : ";
	cin.getline(Name, 70);
	Passengers* curNode, * prevNode;
	curNode = flight->pHead->next;
	prevNode = flight->pHead;
	// If first node has to be deleted
	if (strcmp(prevNode->Name, Name) == 0) {
		flight->pHead = curNode;
		delete prevNode;
	}
	else {
		while (strcmp(curNode->Name, Name) != 0) {
			curNode = curNode->next;
			prevNode = prevNode->next;
		}
		// Deleting last Node
		if (curNode->next == NULL) {
			prevNode->next = NULL;
			delete curNode;
		}
		else {
			prevNode->next = curNode->next;
			delete curNode;
		}
	}
}
void displayPassengers(Flight* flight) {
	Passengers* temp = flight->pHead;
	cout << "\n\nPassengers: " << endl;
	while (temp != NULL) {
		cout << temp->Name << endl;
		temp = temp->next;
	}
	cout << endl;
}

bool isFound(Flight* flight) {
	Passengers* temp = flight->pHead;
	char Name[70];
	cout << "Enter Person Name: ";
	cin.getline(Name, 70);
	while (temp != NULL) {
		if (strcmp(Name, temp->Name) == 0)
			return true;
		temp = temp->next;
	}
	return false;
}
void passengerMenu(Flight* temp) {
	int choice = 0;
	cout << "Airline Ticket Reservation\n\n";
	cout << "1. Reserve Ticket\n2. Cancel Ticket\n3. Check Ticket\n4. Display Passengers\n5.Exit\n\nEnter Choice : ";
	cin >> choice;
	cin.ignore();
	if (choice == 1)
		reserveTicket(temp);
	else if (choice == 2)
		cancelReservation(temp);
	else if (choice == 3)
		cout << (isFound(temp) ? "Yes, Person is Found" : "Person is not Found")
		<< endl;
	else if (choice == 4)
		displayPassengers(temp);
	else if (choice == 5)
		exit(1);
}
void manageFlight() {
	Flight* temp = new Flight;
	temp = fHead;
	char Name[70];
	cout << "Enter Flight Name: ";
	cin.getline(Name, 70);
	while (temp != NULL) {
		if (strcmp(temp->flightName, Name) == 0)
			break;
		temp = temp->next;
	}
	if (temp == NULL) {
		cout << "Flight not Found\n";
		return;
	}
	else {
		passengerMenu(temp);
	}
}

int main() {
	int choice = 0;
	while (true) {
		cout << "Airline Ticket Reservation\n\n";
		cout << "1. Add Flight\n2. Delete Flight\n3. Display Flight\n4. Manage Flight\n5. Exit\n\nEnter Choice: ";
		cin >> choice;
		cin.ignore();
		if (choice == 1)
			addFlight();
		else if (choice == 2)
			deleteFlight();
		else if (choice == 3)
			displayFlight();
		else if (choice == 4)
			manageFlight();
		else if (choice == 5)
			exit(1);
		cout << endl;
	}
	return 0;
}
