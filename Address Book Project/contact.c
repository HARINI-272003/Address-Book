#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "contact.h"

// Toggle favourite flag for a contact
void add_favourites(Contacts *c)
{
    if (c->isFavorite == 0) // If not favourite, mark favourite
    {
        c->isFavorite = 1;
        printf(BLUE "Contact added to favourites.\n" RESET);
    }
    else // If already favourite, turn off
    {
        c->isFavorite = 0;
        printf(RED "Contact removed from favourites.\n" RESET);
    }
}

// Toggle emergency flag for a contact
void add_emergency(Contacts *c)
{
    if (c->isEmergency == 0) // If not emergency, mark emergency
    {
        c->isEmergency = 1;
        printf(BLUE "Contact added as emergency.\n" RESET);
    }
    else // If already emergency, turn off
    {
        c->isEmergency = 0;
        printf(RED "Contact removed from emergency list.\n" RESET);
    }
}

// Create and store a new contact
int create_contact(AddressBook *addressbook)
{
    char name[30], mob[11], mail[30];

    while (1)
    {
        // Read and validate name
        while (1)
        {
            printf("Enter the Name: ");
            scanf(" %[^\n]", name);
            if (name_validation(name))
            {
                strcpy(addressbook->contact_details[addressbook->contact_count].Name, name);
                break;
            }
        }

        // Read, validate and check duplicate mobile
        while (1)
        {
            printf("Enter the Mobile Number: ");
            scanf(" %[^\n]", mob);

            if (!mob_validation(mob))
                continue;

            if (duplicate_mob(addressbook, mob))
            {
                printf(RED "Mobile Number already exists!!! Enter a new number\n" RESET);
                continue;
            }

            strcpy(addressbook->contact_details[addressbook->contact_count].Mobile_number, mob);
            break;
        }

        // Read, validate and check duplicate email
        while (1)
        {
            printf("Enter the Mail ID: ");
            scanf(" %[^\n]", mail);

            if (!mail_validation(mail))
                continue;

            if (duplicate_mail(addressbook, mail))
            {
                printf(RED "Mail ID already exists!!! Enter a new mail id\n" RESET);
                continue;
            }

            strcpy(addressbook->contact_details[addressbook->contact_count].Mail_ID, mail);
            break;
        }

        // Pointer to current contact
        Contacts *c = &addressbook->contact_details[addressbook->contact_count];
        c->isFavorite = 0; // Initialise default flags
        c->isEmergency = 0;

        // Ask favourite marking
        int fav;
        printf("\nMark as Favourite? (1=yes/0=no): ");
        scanf("%d", &fav);
        if (fav == 1)
            add_favourites(c);

        // Ask emergency marking
        int emg;
        printf("\nMark as Emergency? (1=yes/0=no): ");
        scanf("%d", &emg);
        if (emg == 1)
            add_emergency(c);

        // Increase total contact count
        addressbook->contact_count++;
        printf(GREEN "\nContact created successfully.\n" RESET);

        // Ask user to continue adding
        int more;
        printf("\nWant to add another contact? (1=yes/0=no): ");
        scanf("%d", &more);
        if (more == 0)
            break;
    }
    return 0;
}

// Display all contacts
void list_contacts(AddressBook *addressbook)
{
    printf(CYAN " || List of all contacts || \n\n" RESET);

    printf(BLUE "+-----+----------------------+---------------+------------------------------+--------+--------+\n" RESET);
    printf(WHITE "| %-3s | %-20s | %-13s | %-28s | %-6s | %-6s |\n" RESET,
           "No", "Name", "Mobile", "Mail ID", "Fav", "Emg");
    printf(BLUE "+-----+----------------------+---------------+------------------------------+--------+--------+\n" RESET);

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        printf(WHITE "| %-3d | %-20s | %-13s | %-28s | " RESET,
               i + 1,
               addressbook->contact_details[i].Name,
               addressbook->contact_details[i].Mobile_number,
               addressbook->contact_details[i].Mail_ID);

        printf("%s%-6s" RESET,
               addressbook->contact_details[i].isFavorite ? GREEN : RED,
               addressbook->contact_details[i].isFavorite ? "YES" : "NO");

        printf(" | %s%-6s" RESET,
               addressbook->contact_details[i].isEmergency ? GREEN : RED,
               addressbook->contact_details[i].isEmergency ? "YES" : "NO");

        printf(WHITE " |\n" RESET);
    }

    printf(BLUE "+-----+----------------------+---------------+------------------------------+--------+--------+\n" RESET);
}

// list favourite contacts in table form
void list_fav_contacts(AddressBook *addressbook)
{
    printf(CYAN " || List of favourite contacts || \n\n" RESET);

    int found = 0;

    printf(BLUE "+-----+---------------------------+---------------+------------------------------+\n" RESET);
    printf(WHITE "| %-3s | %-25s | %-13s | %-28s |\n" RESET,
           "No", "Name", "Mobile", "Mail ID");
    printf(BLUE "+-----+---------------------------+---------------+------------------------------+\n" RESET);

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (addressbook->contact_details[i].isFavorite == 1)
        {
            printf(WHITE "| %-3d | %-25s | %-13s | %-28s |\n" RESET,
                   i + 1,
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);

            found = 1;
        }
    }

    if (!found)
        printf(RED "No favourite contacts found.\n" RESET);

    printf(BLUE "+-----+---------------------------+---------------+------------------------------+\n\n" RESET);
}

// list emergency contacts in table form
void list_emer_contacts(AddressBook *addressbook)
{
    printf(CYAN " || List of emergency contacts || \n\n" RESET);

    int found = 0;

    printf(BLUE "+-----+---------------------------+---------------+------------------------------+\n" RESET);
    printf(WHITE "| %-3s | %-25s | %-13s | %-28s |\n" RESET,
           "No", "Name", "Mobile", "Mail ID");
    printf(BLUE "+-----+---------------------------+---------------+------------------------------+\n" RESET);

    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (addressbook->contact_details[i].isEmergency == 1)
        {
            printf(WHITE "| %-3d | %-25s | %-13s | %-28s |\n" RESET,
                   i + 1,
                   addressbook->contact_details[i].Name,
                   addressbook->contact_details[i].Mobile_number,
                   addressbook->contact_details[i].Mail_ID);

            found = 1;
        }
    }

    if (!found)
        printf(RED "No emergency contacts found.\n" RESET);

    printf(BLUE "+-----+---------------------------+---------------+------------------------------+\n\n" RESET);
}

// Search a specific contact
int search_contacts(AddressBook *addressbook)
{
    while (1)
    {
        printf(CYAN " || Search Contact menu || \n\n" RESET);
        printf("1. Name\n2. Mobile number\n3. Mail ID\n4. Favourite Contacts\n5. Emergency Contacts\n6. Exit\n\nEnter the option: ");
        int choice;
        scanf("%d", &choice);
        char input[35];

        int matches[100];
        int count = 0;

        // take input
        switch (choice)
        {
        case 1:
            printf("Enter the name: ");
            scanf(" %[^\n]", input);
            break;

        case 2:
            printf("Enter the Mobile number: ");
            scanf(" %[^\n]", input);
            break;

        case 3:
            printf("Enter the mail id: ");
            scanf(" %[^\n]", input);
            break;

        case 4: // favourite search - no input
            break;

        case 5: // emergency search - no input
            break;

        case 6:
            printf(CYAN "THANK YOU!!!\n" RESET);
            return 0;

        default:
            printf(RED "Invalid choice!\n" RESET);
            return 0;
        }

        // direct search
        for (int i = 0; i < addressbook->contact_count; i++)
        {
            if ((choice == 1 && strncasecmp(addressbook->contact_details[i].Name, input, strlen(input)) == 0) ||
                (choice == 2 && strncasecmp(addressbook->contact_details[i].Mobile_number, input, strlen(input)) == 0) ||
                (choice == 3 && strncasecmp(addressbook->contact_details[i].Mail_ID, input, strlen(input)) == 0) ||
                (choice == 4 && addressbook->contact_details[i].isFavorite == 1) ||
                (choice == 5 && addressbook->contact_details[i].isEmergency == 1))
            {
                matches[count++] = i;
            }
        }

        // no match
        if (count == 0)
        {
            printf(RED "No matching contacts found.\n\n" RESET);
            return 0;
        }

        // print matches
        printf(GREEN "\n\nMatching Contacts are:\n" RESET);
        for (int i = 0; i < count; i++)
        {
            int idx = matches[i];
            printf("%d) %s | %s | %s\n",
                   i + 1,
                   addressbook->contact_details[idx].Name,
                   addressbook->contact_details[idx].Mobile_number,
                   addressbook->contact_details[idx].Mail_ID);
        }

        // select contact to view
        printf("\nSelect contact detail needs to be viewed: ");
        int sel;
        scanf("%d", &sel);

        if (sel < 1 || sel > count)
        {
            printf(RED "Invalid selection.\n" RESET);
            return 0;
        }

        int finalIndex = matches[sel - 1];
        Contacts *c = &addressbook->contact_details[finalIndex];

        // Print contact details
        printf("\nName  : %s\n", c->Name);
        printf("Phone : %s\n", c->Mobile_number);
        printf("Mail  : %s\n", c->Mail_ID);
        printf("Favourite : %s\n", c->isFavorite ? "YES" : "NO");
        printf("Emergency : %s\n", c->isEmergency ? "YES" : "NO");

        int more;
        printf("\nDo you want to search another contact: (1=Yes / 0=No): ");
        scanf("%d", &more);
        if (more == 0)
            break;
    }
    return 0;
}

// Edit a contact
int edit_contact(AddressBook *addressbook)
{
    while (1)
    {
        printf(CYAN " || Edit Contact menu || \n\n" RESET);
        printf("1. Name\n2. Mobile number\n3. Mail ID\n4. Favourite contacts\n5. Emergency contacts\n6. Exit\n\nEnter the option: ");

        int choice;
        scanf("%d", &choice);

        char input[35];
        int matches[100], count = 0;

        // Input validation + reading
        switch (choice)
        {
        case 1:
            printf("Enter the name: ");
            scanf(" %[^\n]", input);

            if (!name_validation(input))
                return 0;
            break;

        case 2:
            printf("Enter the mobile number: ");
            scanf(" %[^\n]", input);

            if (!mob_validation(input))
                return 0;
            break;

        case 3:
            printf("Enter the mail id: ");
            scanf(" %[^\n]", input);

            if (!mail_validation(input))
                return 0;
            break;

        case 4:
            // Favourite contacts search — no user input required
            break;

        case 5:
            // Emergency contacts search — no user input required
            break;

        case 6:
            printf(CYAN "THANK YOU!!!\n" RESET);
            return 0;

        default:
            printf(RED "Invalid choice!\n" RESET);
            return 0;
        }

        // Search matching contacts
        for (int i = 0; i < addressbook->contact_count; i++)
        {
            if ((choice == 1 && strncasecmp(input, addressbook->contact_details[i].Name, strlen(input)) == 0) ||
                (choice == 2 && strncasecmp(input, addressbook->contact_details[i].Mobile_number, strlen(input)) == 0) ||
                (choice == 3 && strncasecmp(input, addressbook->contact_details[i].Mail_ID, strlen(input)) == 0) ||
                (choice == 4 && addressbook->contact_details[i].isFavorite == 1) ||
                (choice == 5 && addressbook->contact_details[i].isEmergency == 1))
            {
                matches[count++] = i;
            }
        }

        if (count == 0)
        {
            printf(RED "No matching contacts.\n" RESET);
            return 0;
        }

        // Display matches in list format
        printf(GREEN "\nMatching Contacts:\n" RESET);
        for (int i = 0; i < count; i++)
        {
            int idx = matches[i];
            printf("%d) %s | %s | %s\n",
                   i + 1,
                   addressbook->contact_details[idx].Name,
                   addressbook->contact_details[idx].Mobile_number,
                   addressbook->contact_details[idx].Mail_ID);
        }

        // Select contact index
        int sel;
        printf("\nSelect contact detail needs to be edited: ");
        scanf("%d", &sel);

        if (sel < 1 || sel > count)
        {
            printf(RED "Invalid selection.\n" RESET);
            return 0;
        }

        int editIndex = matches[sel - 1];
        Contacts *c = &addressbook->contact_details[editIndex];

        // Ask field to edit
        int editChoice;
        printf("\nWhat do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Mobile Number\n");
        printf("3. Mail ID\n");
        printf("4. Add / Remove from favourite\n");
        printf("5. Add / Remove from emergency\n");
        printf("Enter your choice: ");
        scanf("%d", &editChoice);

        char newVal[35];

        // Edit respective value
        switch (editChoice)
        {
        case 1:
            while (1)
            {
                printf("Enter the new name: ");
                scanf(" %[^\n]", newVal);
                if (!name_validation(newVal))
                    continue;
                strcpy(c->Name, newVal);
                break;
            }
            break;

        case 2:
            while (1)
            {
                printf("Enter the new mobile number: ");
                scanf(" %[^\n]", newVal);

                if (!mob_validation(newVal))
                    continue;

                int dup = 0;
                for (int i = 0; i < addressbook->contact_count; i++)
                {
                    if (i != editIndex && strcmp(newVal, addressbook->contact_details[i].Mobile_number) == 0)
                    {
                        dup = 1;
                        break;
                    }
                }
                if (dup)
                {
                    printf(RED "Mobile number already exists!\n" RESET);
                    continue;
                }

                strcpy(c->Mobile_number, newVal);
                break;
            }
            break;

        case 3:
            while (1)
            {
                printf("Enter the new mail ID: ");
                scanf(" %[^\n]", newVal);

                if (!mail_validation(newVal))
                    continue;

                int dup = 0;
                for (int i = 0; i < addressbook->contact_count; i++)
                {
                    if (i != editIndex && strcmp(newVal, addressbook->contact_details[i].Mail_ID) == 0)
                    {
                        dup = 1;
                        break;
                    }
                }

                if (dup)
                {
                    printf(RED "Mail ID already exists!\n" RESET);
                    continue;
                }

                strcpy(c->Mail_ID, newVal);
                break;
            }
            break;

        case 4:
            // Toggle favourite option
            int favToggle;
            printf("Add to / Remove from Favourites? (1=YES / 0=NO): ");
            scanf("%d", &favToggle);
            if (favToggle == 1)
                add_favourites(c);
            break;

        case 5:
            // Toggle emergency option
            int emgToggle;
            printf("Add to / Remove from Emergency? (1=YES / 0=NO): ");
            scanf("%d", &emgToggle);
            if (emgToggle == 1)
                add_emergency(c);
            break;

        default:
            printf(RED "Invalid edit choice!\n" RESET);
            return 0;
        }

        // SUCCESS EDIT MESSAGE
        printf(GREEN "\nContact updated successfully!\n\n" RESET);

        // Ask user to continue editing
        int more;
        printf("\nDo you want to edit another contact? (1=Yes / 0=No): ");
        scanf("%d", &more);
        if (more == 0)
            break;
    }
    return 0;
}

// Delete contact
int delete_contact(AddressBook *addressbook)
{
    while (1)
    {
        printf(CYAN "\n || Delete Contact Menu || \n\n" RESET);
        printf("1. Name\n");
        printf("2. Mobile Number\n");
        printf("3. Mail ID\n");
        printf("4. Favourite Contacts\n");
        printf("5. Emergency Contacts\n");
        printf("6. Exit\n\n");
        printf("Enter option: ");

        int choice;
        scanf("%d", &choice);

        char input[35];
        int matches[100], count = 0;

        // Take input using switch
        switch (choice)
        {
        case 1:
            printf("Enter the name: ");
            scanf(" %[^\n]", input);
            break;

        case 2:
            printf("Enter the mobile number: ");
            scanf(" %[^\n]", input);
            break;

        case 3:
            printf("Enter the mail ID: ");
            scanf(" %[^\n]", input);
            break;

        case 4:
            // Favourite contacts deletion — no typed input
            break;

        case 5:
            // Emergency contacts deletion — no typed input
            break;

        case 6:
            printf(CYAN "THANK YOU!!!\n" RESET);
            return 0;

        default:
            printf(RED "Invalid option.\n" RESET);
            return 0;
        }

        // Search matching contacts
        for (int i = 0; i < addressbook->contact_count; i++)
        {
            if ((choice == 1 && strncasecmp(input, addressbook->contact_details[i].Name, strlen(input)) == 0) ||
                (choice == 2 && strncasecmp(input, addressbook->contact_details[i].Mobile_number, strlen(input)) == 0) ||
                (choice == 3 && strncasecmp(input, addressbook->contact_details[i].Mail_ID, strlen(input)) == 0) ||
                (choice == 4 && addressbook->contact_details[i].isFavorite == 1) ||
                (choice == 5 && addressbook->contact_details[i].isEmergency == 1))
            {
                matches[count++] = i;
            }
        }

        if (count == 0)
        {
            printf(RED "No matching contact found.\n" RESET);
            return 0;
        }

        // Print matches
        printf(GREEN "\nMatching Contacts:\n" RESET);
        for (int i = 0; i < count; i++)
        {
            int idx = matches[i];
            printf("%d) %s | %s | %s\n",
                   i + 1,
                   addressbook->contact_details[idx].Name,
                   addressbook->contact_details[idx].Mobile_number,
                   addressbook->contact_details[idx].Mail_ID);
        }

        // Selection
        int sel;
        printf("\nSelect the contact to delete: ");
        scanf("%d", &sel);

        if (sel < 1 || sel > count)
        {
            printf(RED "Invalid selection.\n" RESET);
            return 0;
        }

        int delIndex = matches[sel - 1];

        // Shift contacts
        for (int j = delIndex; j < addressbook->contact_count - 1; j++)
        {
            addressbook->contact_details[j] = addressbook->contact_details[j + 1];
        }

        addressbook->contact_count--;

        printf(GREEN "\nContact deleted successfully!\n" RESET);

        // Ask if want to delete more
        int more;
        printf("\nDo you want to delete another contact? (1=Yes / 0=No): ");
        scanf("%d", &more);

        if (more == 0)
            break;
    }
    return 0;
}

// Save contacts to file
void save_contacts(AddressBook *addressbook)
{
    sortContacts(addressbook);

    printf(CYAN " || Save details ||\n\n" RESET);

    FILE *fp = fopen("data.txt", "w");
    if (!fp)
        return;

    fprintf(fp, "#%d\n", addressbook->contact_count);

    printf("\n");
    for (int i = 1; i <= 100; i++)
    {
        printf(WHITE "Saving contacts: " RESET); // Print start of progress bar
        for (int j = 1; j <= 100; j++)
        {
            if (j <= i)
                printf(SOFT_NEON_GREEN "█" RESET); // Print progress bar filled
            else
                printf(APPLE_GREEN "░" RESET); // Print empty bar space
        }
        printf(WHITE " %d%%" RESET, i); // Display percentage
        fflush(stdout);                 // Flush output buffer
        printf("\r");                   // Return cursor
        usleep(40000);                  // Delay for effect
    }
    // Write each contact + flags
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        fprintf(fp, "%s,%s,%s,%d,%d\n",
                addressbook->contact_details[i].Name,
                addressbook->contact_details[i].Mobile_number,
                addressbook->contact_details[i].Mail_ID,
                addressbook->contact_details[i].isFavorite,
                addressbook->contact_details[i].isEmergency);
    }

    fclose(fp);
    printf(GREEN "\n\nContacts saved successfully.\n" RESET);
}

// Load contacts from file
void loadContactFromTheFile(AddressBook *addressbook)
{
    FILE *fp = fopen("data.txt", "r");
    if (!fp)
        return;

    fscanf(fp, "#%d\n", &addressbook->contact_count);

    printf("\n");
    for (int i = 1; i <= 100; i++)
    {
        printf(WHITE "Loading contacts: " RESET); // Print start of progress bar
        for (int j = 1; j <= 100; j++)
        {
            if (j <= i)
                printf(SOFT_NEON_GREEN "█" RESET); // Print progress bar filled
            else
                printf(APPLE_GREEN "░" RESET); // Print empty bar space
        }
        printf(WHITE " %d%%" RESET, i); // Display percentage
        fflush(stdout);                 // Flush output buffer
        printf("\r");                   // Return cursor
        usleep(40000);                  // Delay for effect
    }

    // Read each contact + flags
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        fscanf(fp, "%[^,],%[^,],%[^,],%d,%d\n",
               addressbook->contact_details[i].Name,
               addressbook->contact_details[i].Mobile_number,
               addressbook->contact_details[i].Mail_ID,
               &addressbook->contact_details[i].isFavorite,
               &addressbook->contact_details[i].isEmergency);
    }
    printf(GREEN "\n\nContacts loaded successfully.\n" RESET);

    fclose(fp);
}

// Sort contacts
void sortContacts(AddressBook *addressbook)
{
    int n = addressbook->contact_count; // Number of contacts
    for (int i = 0; i < n; i++)         // Outer loop
    {
        for (int j = i + 1; j < n; j++) // Inner loop
        {
            if (strcmp(addressbook->contact_details[i].Name,
                       addressbook->contact_details[j].Name) > 0) // Compare names
            {
                Contacts temp = addressbook->contact_details[i]; // Swap
                addressbook->contact_details[i] = addressbook->contact_details[j];
                addressbook->contact_details[j] = temp;
            }
        }
    }
}
