/*       
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP.

       If  act is non-NULL, the new action for signal signum is installed from act.  If
       oldact is non-NULL, the previous action is saved in oldact.

The sigaction structure is defined as something like:

           struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
	
	sa_flags specifies a set of flags which modify the behavior of the  signal.  
	It is formed by the bitwise OR of zero or more of the following:

	If SA_SIGINFO is specified in sa_flags, then  sa_sigaction  (instead  of
       sa_handler)  specifies  the  signal-handling  function for signum.  This
       function receives three arguments.

	   SA_SIGINFO (since Linux 2.2)
              The signal handler takes three arguments, not one.  In this case,
              sa_sigaction should be set instead of sa_handler.  This  flag  is
              meaningful only when establishing a signal handler.
	When the SA_SIGINFO flag is set, the prototype handler looks like this:
	
	void handler (int sig, siginfo_t * info, void * context);
	
	When SA_SIGINFO is sent, the “capture” function takes three input arguments:
	“sig” which specifies the signal
	- a structure of type “signinfo_t” which contains the detailed information about
		the process that sent the signal and context
	- a pointer to the “ucontext_t structure” that stores the context information on
		the kernel stack. This argument isn’t used, so the NULL pointer is sent.


 siginfo_t
              Include: <signal.h>.  Alternatively, <sys/wait.h>.

              typedef struct {
                  int      si_signo;  // Signal number 
                  int      si_code;   // Signal code 
                  pid_t    si_pid;    // Sending process ID 
                  uid_t    si_uid;    // Real user ID of sending process 
                  void    *si_addr;   // Address of faulting instruction 
                  int      si_status; // Exit value or signal 
                  union sigval si_value;  // Signal value 
              } siginfo_t;

int sigemptyset(sigset_t *set); 

 sigset_t
              Include: <signal.h>.  Alternatively, <spawn.h>, or <sys/select.h>.

              This is a type that represents  a  set  of  signals.   According  to
              POSIX, this shall be an integer or structure type.

*/

#include "minitalk.h"

void     signal_handler(int signal, siginfo_t *info, void *context)
{
	static char		c;
	static int		bits;
	(void)context;

	if (signal == SIGUSR1)
		c = (c << 1) | 0; // Shift left by 1 and set LSB to 0
    else if (signal == SIGUSR2)
	{
    	c = (c << 1) | 1;
	} // Shift left by 1 and set LSB to 1

	//printf("Signal: %d, Bit: %d, Character: %c\n", signal, c & 1, c);
	bits++; 		// +1 per signal recieved
	if (bits == 8) // full byte recieved
	{
		if (c == '\0')
		{
			ft_putchar_fd('\n', 1);
			kill(info->si_pid, SIGUSR1);
		}
		ft_putchar_fd(c, 1);
		bits = 0;
		c = 0;
	}
	else
		c <<= 1; // shifts c 1 bit to the left
}

int	main(void)
{
	struct sigaction	act;
	
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}