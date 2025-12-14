#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

// Name validation
int name_validation(char *name)
{
    while (1)
    {
        int valid = 1; // validity flag

        // empty
        if (name[0] == '\0')
        {
            printf(RED "Name cannot be empty! Try again.\n" RESET);
            valid = 0; // invalid
        }
        // starts with space
        else if (name[0] == ' ')
        {
            printf(RED "Name must not start with a space! Try again.\n" RESET);
            valid = 0; // invalid
        }
        // length check
        else if (strlen(name) > 30)
        {
            printf(RED "Name is too long! Max 30 characters.\n" RESET);
            valid = 0; // invalid
        }
        else
        {
            // check characters
            for (int i = 0; name[i] != '\0'; i++)
            {
                if (name[i] == ' ' && name[i + 1] == ' ')
                {
                    printf(RED "Name should not contain multiple spaces! Try again.\n" RESET);
                    valid = 0; // invalid
                    break;
                }

                if (!(isalpha(name[i]) || name[i] == ' '))
                {
                    printf(RED "Name must contain only alphabets! Try again.\n" RESET);
                    valid = 0; // invalid
                    break;
                }
            }
        }

        if (valid)
            return 1; // valid input

        printf("Enter Name again: ");
        scanf(" %[^\n]", name); // re-input
    }
}

// Mobile validation
int mob_validation(char *mob)
{
    while (1)
    {
        int valid = 1; // validity flag

        // empty
        if (mob[0] == '\0' || mob[0] == ' ')
        {
            printf(RED "Mobile number cannot be empty! Try again.\n" RESET);
            valid = 0; // invalid
        }
        else
        {
            // only digits
            for (int i = 0; mob[i] != '\0'; i++)
            {
                if (!isdigit(mob[i]))
                {
                    printf(RED "Mobile number must contain digits only! Try again.\n" RESET);
                    valid = 0; // invalid
                    break;
                }
            }
        }

        // length check
        if (valid && strlen(mob) != 10)
        {
            printf(RED "Mobile number must have exactly 10 digits! Try again.\n" RESET);
            valid = 0; // invalid
        }

        // starting digit check
        if (valid && (mob[0] < '6' || mob[0] > '9'))
        {
            printf(RED "Mobile number must start with 6, 7, 8, or 9! Try again.\n" RESET);
            valid = 0; // invalid
        }

        if (valid)
            return 1; // valid input

        printf("Enter Mobile again: ");
        scanf(" %[^\n]", mob); // re-input
    }
}

// Mail validation
int mail_validation(char *mail)
{
    while (1)
    {
        int valid = 1; // validity flag

        // empty
        if (mail[0] == '\0' || mail[0] == ' ')
        {
            printf(RED "Mail ID cannot be empty! Try again.\n" RESET);
            valid = 0; // invalid
        }
        // cannot start with @ or .
        else if (mail[0] == '@' || mail[0] == '.')
        {
            printf(RED "Mail ID cannot start with '@' or '.'! Try again.\n" RESET);
            valid = 0; // invalid
        }

        // check @
        char *at = strchr(mail, '@'); // pointer to @
        if (valid && !at)
        {
            printf(RED "Mail ID must contain '@'! Try again.\n" RESET);
            valid = 0; // invalid
        }

        // check .com
        char *dotcom = strstr(mail, ".com");
        if (valid && !dotcom)
        {
            printf(RED "Mail ID must contain '.com'! Try again.\n" RESET);
            valid = 0;
        }
        else if (valid && strcmp(dotcom, ".com") != 0)
        {
            printf(RED "'.com' must be correctly written! Try again.\n" RESET);
            valid = 0;
        }

        int has_alpha = 0; // alphanumeric check
        for (int i = 0; mail[i] != '@'; i++)
        {
            if (valid && !(isalnum(mail[i])))
            {
                printf(RED "Mail ID must contain alphanumeric characters! Try again.\n" RESET);
                valid = 0; // invalid
                break;
            }
            if (isalpha(mail[i]))
            {
                has_alpha = 1;
            }
        }
        if (valid && has_alpha == 0)
        {
            printf(RED "Mail ID must contain at least one alphabet before '@'! Try again.\n" RESET);
            valid = 0;
        }

        // order check
        if (valid && at > dotcom)
        {
            printf(RED "'.com' must come after '@'! Try again.\n" RESET);
            valid = 0; // invalid
        }

        int at_count = 0; // check multiple @
        for (int i = 0; mail[i] != '\0'; i++)
        {
            if (mail[i] == '@')
            {
                at_count++;
            }
        }
        if (at_count > 1)
        {
            printf(RED "Multiple '@' symbols are present!!! Use only one '@'\n" RESET);
            valid = 0; // invalid
        }

        int dot_count = 0; // check multiple dots
        for (int i = 0; mail[i] != '\0'; i++)
        {
            if (mail[i] == '.')
            {
                dot_count++;
            }
        }
        if (dot_count > 1)
        {
            printf(RED "Multiple '.' are present!!! Use only one '.'\n" RESET);
            valid = 0; // invalid
        }

        // domain validation
        if (valid && at < dotcom)
        {
            char domain[30]; // store domain
            int idx = 0;     // index

            for (char *p = at + 1; p < dotcom; p++)
                domain[idx++] = *p; // copy characters

            domain[idx] = '\0'; // terminate string

            // empty domain
            if (idx == 0)
            {
                printf(RED "Domain name cannot be empty! Try again.\n" RESET);
                valid = 0; // invalid
            }

            // domain characters
            for (int i = 0; valid && i < idx; i++)
            {
                if (!islower(domain[i]))
                {
                    printf(RED "Domain must contain lowercase letters only! Try again.\n" RESET);
                    valid = 0; // invalid
                }
            }
        }

        // uppercase check
        if (valid)
        {
            for (int i = 0; mail[i] != '\0'; i++)
            {
                if (isupper(mail[i]))
                {
                    printf(RED "Mail ID must not contain uppercase letters! Try again.\n" RESET);
                    valid = 0; // invalid
                    break;
                }
            }
        }

        if (valid)
            return 1; // valid input

        printf("Enter Mail ID again: ");
        scanf(" %[^\n]", mail); // re-input
    }
}

// Mobile duplicate
int duplicate_mob(AddressBook *addressbook, char *mobile)
{
    for (int i = 0; i < addressbook->contact_count; i++) // Loop contacts
    {
        if (strcmp(addressbook->contact_details[i].Mobile_number, mobile) == 0) // Compare numbers
        {
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicate
}

// Mail duplicate
int duplicate_mail(AddressBook *addressbook, char *email)
{
    for (int i = 0; i < addressbook->contact_count; i++) // Loop contacts
    {
        if (strcmp(addressbook->contact_details[i].Mail_ID, email) == 0) // Compare emails
        {
            return 1; // Duplicate found
        }
    }
    return 0; // No duplicate
}
