#include "clientServerThreads.h"

void *client_thread (void *args)
{
    int socket_fd;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    char host_name [MAX_LINE_SIZE];
    int host_port_no;
    struct server_address server_table [MAX_SERVERS];
    int server_count;
    char send_line [MAX_LINE_SIZE];
    char work_c_string [MAX_LINE_SIZE];
    char caller [MAX_LINE_SIZE];
    int i;


    gethostname (host_name, sizeof (host_name));
    sprintf (caller, "    Client [%s]", host_name);
    printf ("    Client [HOST=%s PID=%d]: ready\n", host_name, getpid ());

    /* Don't start until server is ready */
    while (SERVER_NOT_READY)
    {
        mutex_lock (caller);
        if (*my_server_ready)
        {
            break;
        }
        mutex_unlock (caller);
    }
    /* Don't start until client is ready */
    server_count = get_server_addresses (server_table);
    for (i = 0; i < server_count; i ++)
    {
        if (strcmp (host_name, server_table [i].host_name) == 0)
        {
            host_port_no = server_table [i].port_no;
            break;
        }
    }
    mutex_unlock (caller);

    srand (host_port_no);

    while (LOOP_FOREVER)
    {
        printf ("    Client [HOST=%s PID=%d]: ENTERING NON-CRITICAL SECTION\n", host_name, getpid ());
        usleep (2000 * (1 + rand () % 1000));
        printf ("    Client [HOST=%s PID=%d]: LEAVING NON-CRITICAL SECTION\n", host_name, getpid ());

        /* THE REQUEST PART OF YOUR PRE-PROTOCOL CODE GOES HERE! */

        //*my_ticket_no = 0;
        //*my_highest_ticket_no = 0;
        // mutex lock
        mutex_lock(caller);

        *my_request = 1;
        *my_highest_ticket_no = *my_highest_ticket_no + 1;
        *my_ticket_no = *my_highest_ticket_no;
        //*my_replies = 0;

        // ----------------- Building request message -----------------------
        memset(send_line, 0, strlen(send_line));
        strcat(send_line, "request ");
        strcat(send_line, host_name);

        // Convert host port no to c string and append to send line 
        sprintf(work_c_string, " %i", host_port_no);
        strcat(send_line, work_c_string);

        // Covert my ticket number to c string and append to send line 
        sprintf(work_c_string, " %i", *my_ticket_no);
        strcat(send_line, work_c_string);

        // Add terminal character ()
        send_line[strlen(send_line)] = '\0';

        // Loop and send message to each server in the network
        for (i = 0; i < server_count; i++) {
            // Avoid sending message to itself
            if (strcmp (host_name, server_table [i].host_name) != 0) {
                // Socket system call
                if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                    printf("ClientThread: socket ERROR");
                    exit(1);
                }

                // Socket setup
                memset(&server_addr, 0, sizeof(server_addr));
                server_addr.sin_family = AF_INET;
                hp = gethostbyname(server_table[i].host_name);
                if (hp == (struct hostent *) NULL) {
                    printf("ClientThread: gethostbyname ERROR: %s does not exist", server_table[i].host_name);
                    exit(1);
                }
                memcpy(&server_addr.sin_addr, hp->h_addr, hp->h_length);
                server_addr.sin_port = htons(server_table[i].port_no);

                // Connect system call
                if (connect (socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
                    printf("ClientThread: connect ERROR");
                    exit(1);
                }

                // Send request message
                send_message (socket_fd, send_line, caller);
                printf ("Client [HOST=%s PID=%d]: SENDING REQUEST MESSAGE TO [HOST=%s]\n", host_name, getpid(), server_table [i].host_name);

                close (socket_fd);
            }
        }
        // mutex unlock
        mutex_unlock(caller);
        // -------------------- END OF REQUEST PART OF PRE_PROTOCOL ------------------------

        printf ("    Client [HOST=%s PID=%d]: WAITING TO ENTER CRITICAL SECTION\n", host_name, getpid ());
        while (AWAIT_REPLIES)
        {

            /* THE AWAIT REPLIES PART OF YOUR PRE-PROTOCOL CODE GOES HERE! */
            mutex_lock(caller);

            if (*my_replies < server_count - 1) {
                mutex_unlock(caller);
            }
            else {
                *my_replies = 0;
                mutex_unlock(caller);
                break;
            }
            // ------ END OF AWAIT REPLIES PART OF PRE-PROTOCOL -------
        }
        printf ("    Client [HOST=%s PID=%d]: ENTERING CRITICAL SECTION\n", host_name, getpid ());
        write_to_history_file (host_name, host_port_no, my_ticket_no);
        printf ("    Client [HOST=%s PID=%d]: LEAVING CRITICAL SECTION\n", host_name, getpid ());

        /* THE DEFERRED REPLIES OF YOUR POST-PROTOCOL CODE GOES HERE! */

        char deferred_message[MAX_LINE_SIZE];

        mutex_lock(caller);
        *my_request = 0;

        printf ("Client [HOST=%s PID=%d]: my_deferred_count=%i\n", host_name, getpid(), *my_deferred_count);

        // Loop and send deferred message to each server in the network
        for (i = 0; i < *my_deferred_count; i++) {
            // ----------------- Building reply message -----------------------
            memset(deferred_message, 0, strlen(deferred_message));
            strcat(deferred_message, "reply ");
            strcat(deferred_message, (my_deferred_table + i * sizeof(my_deferred_table))->host_name);

            // Convert host port no to c string and append to deferred message
            sprintf(work_c_string, " %i", (my_deferred_table + i * sizeof(my_deferred_table))->port_no);
            strcat(deferred_message, work_c_string);


            // Add terminal character ()
            deferred_message[strlen(send_line)] = '\0';
    
            // Socket system call
            if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                printf("ClientThread: socket ERROR");
                exit(1);
            }

            // Socket setup
            memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sin_family = AF_INET;
            hp = gethostbyname((my_deferred_table + i * sizeof(my_deferred_table))->host_name);
            if (hp == (struct hostent *) NULL) {
                printf("ClientThread: gethostbyname ERROR: %s does not exist", (my_deferred_table + i * sizeof(my_deferred_table))->host_name);
                exit(1);
            }
            memcpy(&server_addr.sin_addr, hp->h_addr, hp->h_length);
            server_addr.sin_port = htons((my_deferred_table + i * sizeof(my_deferred_table))->port_no);

            // Connect system call
            if (connect (socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
                printf("ClientThread: connect ERROR");
                exit(1);
            }

            // Send request message
            send_message (socket_fd, deferred_message, caller);
            printf ("Client [HOST=%s PID=%d]: SENDING DEFERRED MESSAGE TO [HOST=%s]\n", host_name, getpid(), (my_deferred_table + i * sizeof(my_deferred_table))->host_name);
            close (socket_fd);

            //Eliminate the host from deferred table
            //strcpy(my_deferred_table[i]->host_name, "\0");
            //my_deferred_table[i]->port_no = 0;
        }
        *my_deferred_count = 0;

        mutex_unlock(caller);

    }

    exit (0);
}

int get_server_addresses (struct server_address server_table [])
{
    FILE *server_address_file;
    char char_port_no [MAX_LINE_SIZE];
    int int_port_no;
    int server_count = 0;
    int lock;
    struct flock key;

    key.l_type = F_WRLCK;
    key.l_whence = SEEK_SET;
    key.l_start = 0;
    key.l_len = 0;
    key.l_pid = getpid ();
    lock = open ("server_address_file_lock", O_WRONLY);
    fcntl (lock, F_SETLKW, &key);

    server_address_file = fopen ("serverAddressFile", "r");
    if (server_address_file == (FILE *) NULL)
    {
        printf ("    Client: fopen failed for serverAddressFile read");
        exit (1);
    }

    while (fscanf (server_address_file, "%s", server_table [server_count].host_name) == 1)
    {
        fscanf (server_address_file, "%s", char_port_no);
        int_port_no = atoi (char_port_no);
        server_table [server_count].port_no = int_port_no;
        server_count ++;
    }

    fclose (server_address_file);

    key.l_type = F_UNLCK;
    fcntl (lock, F_SETLK, &key);
    close (lock);

    return (server_count);
}

void write_to_history_file (char host_name [], int host_port_no, int *my_ticket_no)
{
    FILE *history_file;

    history_file = fopen ("historyFile", "a");
    if (history_file == (FILE *) NULL)
    {
        printf ("    Client: fopen failed for historyFile append");
        exit (1);
    }

    fprintf (history_file, "%s\n", host_name);
    fprintf (history_file, "%d\n", host_port_no);
    fprintf (history_file, "%d\n\n", *my_ticket_no);

    fclose (history_file);

    return;
}
