#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

class L_KeyGetter {
private:
	struct termios oldSettings, newSettings;
	fd_set set;
    struct timeval tv;
    
public:
	~L_KeyGetter() {
		tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
	};
	L_KeyGetter(unsigned int input_sec, unsigned int input_usec) {
		tcgetattr( fileno( stdin ), &oldSettings );
    	newSettings = oldSettings;
    	newSettings.c_lflag &= (~ICANON & ~ECHO);
    	tcsetattr( fileno( stdin ), TCSANOW, &newSettings );
    	tv.tv_sec = input_sec;
        tv.tv_usec = input_usec; 
	};
	bool KGet(char * input_cbuf) {
		FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );

        int res = select( fileno( stdin )+1, &set, NULL, NULL, &tv );

        if( res > 0 )
        {
            read( fileno( stdin ), input_cbuf, 1 );
            return true;
        }
        else if( res < 0 )
        {
            perror( "select error" );
            return false;
        }
        else
        {
            printf( "Select timeout\n" );
            return false;
        }
	};
};
