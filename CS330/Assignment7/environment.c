#include "environment.h"

int main ()
{
    int socket_fd;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    char host_name [MAX_LINE_SIZE];
    struct server_address server_table [MAX_SERVERS];
    int server_count;
    char send_line [MAX_LINE_SIZE];
    int i;

    gethostname (host_name, sizeof (host_name));
    if (strcmp (host_name, "hercules") == 0)
    {
        printf ("Ricart-Agrawala: environment node will not run on hercules\n");
        return 1;
    }
    else if (strcmp (host_name, "a049831") == 0)
    {
        printf ("Ricart-Agrawala: environment node will not run on a049831\n");
        return 1;
    }

    server_count = get_server_addresses (server_table);

    /* Start servers */
    printf ("Environment [HOST=%s PID=%d}: Press [ctrl/d] to start", host_name, getpid ());
    scanf ("%s", send_line);
    printf ("\n");
    strcpy (send_line, "start");
    for (i = 0; i < server_count; i ++)
    {
        if ((socket_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf ("socket ERROR in main");
            exit (1);
        }
        memset (&server_addr, 0, sizeof (server_addr));
        server_addr.sin_family = AF_INET;
        hp = gethostbyname (server_table [i].host_name);
        if (hp == (struct hostent *) NULL)
        {
            printf ("gethostbyname ERROR in main: %s does not exist", server_table [i].host_name);
            exit (1);
        }
        memcpy (&server_addr.sin_addr, hp -> h_addr, hp -> h_length);
        server_addr.sin_port = htons (server_table [i].port_no);
        if (connect (socket_fd, (struct sockaddr *) &server_addr, sizeof (server_addr)) < 0)
        {
            printf ("connect ERROR in main");
            exit (1);
        }
        printf ("Environment [HOST=%s PID=%d]: [%s] sent to [HOST=%s PORT=%d]\n", host_name, getpid (), send_line, server_table [i].host_name, server_table [i].port_no);
        send_message (socket_fd, send_line);
        close (socket_fd);
    }

    /* Shutdown servers */
    printf ("Environment [HOST=%s PID=%d]: Press [ctrl/d] to shutdown ", host_name, getpid ());
    scanf ("%s", send_line);
    printf ("\n");
    strcpy (send_line, "shutdown");
    for (i = 0; i < server_count; i ++)
    {
        if ((socket_fd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf ("socket ERROR in main");
            exit (1);
        }
        memset (&server_addr, 0, sizeof (server_addr));
        server_addr.sin_family = AF_INET;
        hp = gethostbyname (server_table [i].host_name);
        if (hp == (struct hostent *) NULL)
        {
            printf ("gethostbyname ERROR in main: %s does not exist", server_table [i].host_name);
            exit (1);
        }
        memcpy (&server_addr.sin_addr, hp -> h_addr, hp -> h_length);
        server_addr.sin_port = htons (server_table [i].port_no);
        if (connect (socket_fd, (struct sockaddr *) &server_addr, sizeof (server_addr)) < 0)
        {
            close (socket_fd);
            continue;        
        }
        printf ("Environment [HOST=%s PID=%d]: [%s] sent to [HOST=%s PORT=%d]\n", host_name, getpid (), send_line, server_table [i].host_name, server_table [i].port_no);
        send_message (socket_fd, send_line);
        close (socket_fd);
    }
    remove ("serverAddressFile");

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
        printf ("clientThread: fopen ERROR");
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

void send_message (int socket_fd, char send_line [])
{
    int i;
    int n;

    n = strlen (send_line);
    if ((i = write_n (socket_fd, send_line, n)) != n)
    {
        printf ("Environment: write_n failed in send_message");
	exit (1);
    }

    return;
}

int write_n (int fd, char *ptr, int n_bytes)
{
    int n_left;
    int n_written;

    n_left = n_bytes;

    while (n_left > 0)
    {
        n_written = write (fd, ptr, n_left);
        if (n_written <= 0)
        {
            return (n_written);
        }
        n_left = n_left - n_written;
        ptr = ptr + n_written;
    }

    return (n_bytes - n_left);
}
