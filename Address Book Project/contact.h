#ifndef CONTACT_H
#define CONTACT_H

#define RED "\033[1;31m"                  // Error / Invalid
#define GREEN "\033[1;32m"                // Success messages
#define CYAN "\033[1;36m"                 // Headings / section titles
#define WHITE "\033[1;37m"                // Normal text / table text
#define BLUE "\033[1;34m"                 // Table borders / separators
#define APPLE_GREEN "\033[38;2;168;228;160m"
#define SOFT_NEON_GREEN "\033[38;2;120;255;100m"
#define RESET "\033[0m"

typedef struct Contact_data
{
    char Name[32];          // Contact name
    char Mobile_number[11]; // Phone number
    char Mail_ID[35];
    int isFavorite;  // 0 = No, 1 = Yes
    int isEmergency; // 0 = No, 1 = Yes   
} Contacts;

typedef struct AddressBook_Data
{
    Contacts contact_details[100]; // Contact list
    int contact_count;             // Number of contacts
} AddressBook;

void add_favourites(Contacts *c);
void add_emergency(Contacts *c);
void list_fav_contacts(AddressBook *addressbook);
void list_emer_contacts(AddressBook *addressbook);
void loadContactFromTheFile(AddressBook *); // Load contacts
void sortContacts(AddressBook *);           // Sort contacts
int name_validation(char *);                // Validate name
int mail_validation(char *);                // Validate email
int mob_validation(char *);                 // Validate phone
int duplicate_mob(AddressBook *, char *);   // Check phone duplicate
int duplicate_mail(AddressBook *, char *);  // Check email duplicate
int create_contact(AddressBook *);          // Create contact
void list_contacts(AddressBook *);          // List contacts
int search_contacts(AddressBook *);         // Search contact
int edit_contact(AddressBook *);            // Edit contact
int delete_contact(AddressBook *);          // Delete contact
void save_contacts(AddressBook *);          // Save contacts

#endif
