/*
NAME: S HARINI
DATE: 07-12-2025
SAMPLE INPUT: Name: Harini
              Phone number: 6589741230
              Mail ID: hari@gmail.com

SAMPLE OUTPUT: Contacts saved successfully
               #1
               Harini,6589741230,hari@gmail.com

Description: > A simple Address Book program in C to store and manage contacts.
             > It allows users to create new contacts by entering name, phone number, and mail id.
             > The program checks that the name is not empty and contains only alphabetic characters in a proper format.
             > The program ensures the phone number has exactly ten digits and contains only numeric characters.
             > The program verifies that the email has a proper structure with one '@' symbol and a valid domain format.
*/

#include <stdio.h>
#include "contact.h"

int main()
{
    AddressBook addressbook; // Address book object

    int option;                           // menu choice
    addressbook.contact_count = 0;        // initialize count
    loadContactFromTheFile(&addressbook); // load existing data

    while (1) // main loop
    {
        printf(CYAN "\n   ::: Address book menu :::\n\n" RESET); /* menu text */
        printf("1. Add contact\n2. Search contact\n3. Edit contact\n4. Delete contact\n5. List all contacts\n6. List Favourite contact\n7. List Emergency contacts\n8. Save details\n9. EXIT\n");
        printf("\nEnter the option from the above menu: ");
        scanf("%d", &option);
        printf("\n");

        switch (option) // menu handler
        {
        case 1:
            create_contact(&addressbook); // add contact
            break;

        case 2:
            search_contacts(&addressbook); // search contact
            break;

        case 3:
            edit_contact(&addressbook); // edit contact
            break;

        case 4:
            delete_contact(&addressbook); // delete contact
            break;

        case 5:
            list_contacts(&addressbook); // display contacts
            break;

        case 6:
            list_fav_contacts(&addressbook); // display favourite contacts
            break;

        case 7:
            list_emer_contacts(&addressbook); // display emergency contacts
            break;

        case 8:
            save_contacts(&addressbook); // save and exit
            break;

        case 9:
            printf(CYAN " || EXIT ||\n\n" RESET);
            printf(GREEN "Exiting from main menu!!!\n\n" RESET);
            return 0; // exit program

        default:
            printf(RED "Invalid option!!!\n" RESET); // wrong input
            break;
        }
    }
    return 0; // program end
}