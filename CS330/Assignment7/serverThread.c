#include "clientServerThreads.h"

void *server_thread (void *args)
{
    int socket_fd;
    int new_socket_fd;
    int addr_length;
    int child_pid;
    int child_status;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    struct hostent *hp;
    char host_name [MAX_LINE_SIZE];
    int source_socket_fd;
    struct sockaddr_in source_addr;
    char message_type [MAX_LINE_SIZE];
    char source_host_name [MAX_LINE_SIZE];
    char source_port_no [MAX_LINE_SIZE];
    char source_ticket_no [MAX_LINE_SIZE];
    char recv_line [MAX_LINE_SIZE];
    char send_line [MAX_LINE_SIZE];
    char work_c_string [MAX_LINE_SIZE];
    char caller [MAX_LINE_SIZE];

    if ((socket_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf ("Server: socket failed");
        exit (1);
    }

    memset (&server_addr, 0, sizeof (server_addr));
    server_addr.sin_family = AF_INET;
    gethostname (host_name, sizeof (host_name));
    hp = gethostbyname (host_name);
    if (hp == (struct hostent *) NULL)
    {
        printf ("Server: gethostbyname failed (%s does not exist)", host_name);
        exit (1);
    }

    sprintf (caller, "Server [%s]", host_name);
    memcpy (&server_addr.sin_addr, hp -> h_addr, hp -> h_length);
    server_addr.sin_port = htons (0);
    if (bind (socket_fd, (struct sockaddr *) &server_addr, sizeof (server_addr)) < 0)
    {
        printf ("Server: bind failed");
        exit (1);
    }

    addr_length = sizeof (server_addr);
    if (getsockname (socket_fd, (struct sockaddr *) &server_addr, &addr_length) < 0)
    {
        printf ("Server: getsockname failed");
        exit (1);
    }

    if (listen (socket_fd, 128) < 0)
    {
        printf ("Server: listen failed");
        exit (1);
    }
    publish_server_address (host_name, ntohs (server_addr.sin_port));
    printf ("Server [HOST=%s PID=%d]: ready and listening on [PORT=%d]\n", host_name, getpid (), ntohs (server_addr.sin_port));

    while (LOOP_FOREVER)
    {
        addr_length = sizeof (client_addr);
        new_socket_fd = accept (socket_fd, (struct sockaddr *) &client_addr, &addr_length);
        if (new_socket_fd < 0)
        {
            printf ("Server: accept failed");
            exit (1);
        }
        mutex_lock (caller);
        get_message (new_socket_fd, recv_line, "Server");
        close (new_socket_fd);
        parse_message (recv_line, message_type, source_host_name, source_port_no, source_ticket_no);
        printf ("Server [HOST=%s PID=%d]: received [%s]\n", host_name, getpid (), recv_line);
        mutex_unlock (caller);
        if (strcmp (message_type, "start") == 0)
        {
            mutex_lock (caller);
            *my_server_ready = 1;
            mutex_unlock (caller);
            continue;
        }
        else if (strcmp (message_type, "shutdown") == 0)
        {
            close (socket_fd);
            return ((void *) NULL);
        }
        if ((child_pid = fork ()) < 0)
        {
            printf ("Server: fork failed");
            exit (1);
        }
        else if (child_pid == 0)
        {
            /* YOUR REQUEST, REPLY, AND DEFERRED REPLY CODE GOES HERE! */
            mutex_lock(caller);

            // ---------- REQUEST PART ------------------
            if (strcmp (message_type, "request") == 0) {
                printf ("Server [HOST=%s PID=%d]: RECEIVE REQUEST MESSAGE FROM [HOST=%s]\n", host_name, getpid(), source_host_name);

                *my_highest_ticket_no = (*my_highest_ticket_no < atoi(source_ticket_no)) ? atoi(source_ticket_no) : *my_highest_ticket_no;
                printf ("Server [HOST=%s PID=%d]: my_ticket_no = %i\n", host_name, getpid(), source_host_name, *my_ticket_no);
    

                // ------ Send reply message after receiving request
                if (*my_request == 0 || atoi(source_ticket_no) < *my_ticket_no || (atoi(source_ticket_no) == *my_ticket_no && strcmp(source_host_name, host_name) < 0)){

                    // -------- Build reply message --------------
                    memset(send_line, 0, strlen(send_line));
                    strcat(send_line, "reply ");
                    strcat(send_line, host_name);

                    sprintf(work_c_string, " %i", (int)server_addr.sin_port);
                    strcat(send_line, work_c_string);

                    sprintf(work_c_string, " %i", my_highest_ticket_no);
                    strcat(send_line, work_c_string);

                    send_line[strlen(send_line)] = '\0';

                    // ------------- Socket setup -----------------
                    if ((source_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                        printf("Server - child : socket ERROR");
                        exit(1);
                    }
                    memset(&source_addr, 0, sizeof(source_addr));
                    source_addr.sin_family = AF_INET;
                    hp = gethostbyname(source_host_name);
                    if (hp == (struct hostent *) NULL) {
                        printf ("Server - child : gethostbyname ERROR: %s does not exist", source_host_name);
                        exit(1);
                    }
                    memcpy(&source_addr.sin_addr, hp->h_addr, hp->h_length);
                    source_addr.sin_port = htons(atoi(source_port_no));

                    // ------- Socket connect system call --------------
                    if (connect (source_socket_fd, (struct sockaddr *) &source_addr, sizeof(source_addr)) < 0) {
                        printf("Server - child : connect ERROR");
                        exit(1);
                    }

                    // --------- Send reply message ---------------
                    send_message(source_socket_fd, send_line, caller);
                    printf ("Server [HOST=%s PID=%d]: SENDING REPLY MESSAGE TO [HOST=%s]\n", host_name, getpid(), source_host_name);

                    close (source_socket_fd);
                }
                // ------- Defer reply message ---------------
                else {
                    strcpy((my_deferred_table + (*my_deferred_count) * sizeof(my_deferred_table))->host_name, source_host_name);
                    (my_deferred_table + (*my_deferred_count) * sizeof(my_deferred_table))->port_no = atoi(source_port_no);
                    printf ("Server [HOST=%s PID=%d]: request is deferred from %s\n", host_name, getpid(), source_host_name);

                    *my_deferred_count = *my_deferred_count + 1;
                    printf ("Server [HOST=%s PID=%d]: my_deferred_count = %i\n", host_name, getpid(), *my_deferred_count);

                }
            }

            // ---------- REPLY PART ---------------------
            else if (strcmp (message_type, "reply") == 0) {
                printf ("Server [HOST=%s PID=%d]: RECEIVE REPLY MESSAGE FROM [HOST=%s]\n", host_name, getpid(), source_host_name);

                *my_replies = *my_replies + 1;
                printf ("Server [HOST=%s PID=%d]: my_replies = %i\n", host_name, getpid(), *my_replies);
            }
            
            mutex_unlock(caller);

            // ------ END OF REQUEST, REPLY, AND DEFERRED REPLY ---------

        }
        do
        {
            child_pid = waitpid (-1, &child_status, WNOHANG);
        } while (child_pid > 0);
    }

    exit (0);
}

void publish_server_address (char host_name [], int port_no)
{
    FILE *server_address_file;
    int lock;
    struct flock key;

    key.l_type = F_WRLCK;
    key.l_whence = SEEK_SET;
    key.l_start = 0;
    key.l_len = 0;
    key.l_pid = getpid ();
    lock = open ("server_address_file_lock", O_WRONLY);
    fcntl (lock, F_SETLKW, &key);

    server_address_file = fopen ("serverAddressFile", "a");
    if (server_address_file == (FILE *) NULL)
    {
        printf ("Server: fopen failed for serverAddressFile append");
        exit (1);
    }

    fprintf (server_address_file, "%s\n", host_name);
    fprintf (server_address_file, "%d\n", port_no);

    fclose (server_address_file);

    key.l_type = F_UNLCK;
    fcntl (lock, F_SETLK, &key);
    close (lock);

    return;
}

void parse_message (char recv_line [], char message_type [], char source_host_name [], char source_port_no [], char source_ticket_no [])
{
    char message [MAX_LINE_SIZE];
    char tokens [MAX_TOKENS][MAX_LINE_SIZE];

    strcpy (message, recv_line);
    tokenize_message (tokens, message);

    strcpy (message_type, tokens [0]);
    strcpy (source_host_name, tokens [1]);
    strcpy (source_port_no, tokens [2]);
    strcpy (source_ticket_no, tokens [3]);

    return;
}

int tokenize_message (char tokens [][MAX_LINE_SIZE], char message [])
{
    char *token;
    int i;

    for (i = 0; i < MAX_TOKENS; i ++)
    {
        strcpy (tokens [i], "");
    }

    if ((token = strtok (message, " ")) != NULL)
    {
        strcpy (tokens [0], token);
        i = 1;
        while ((token = strtok (NULL, " ")) != NULL)
        {
            strcpy (tokens [i], token);
            i ++;
        }
    }

    return i;
}
