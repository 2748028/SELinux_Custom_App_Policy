/* -----------------------------------------------------------
 * OS Security SELinux Project - Application to Confine
 * -----------------------------------------------------------
 * Imagine this is a custom application that your organization
 * wants to run, and that the main actions it takes are risky, 
 * so you have been asked to confine it using SELinux.
 *
 * Refer to the SELinux tutorial for a good starting point for
 * learning how to confine a process.  If you need help, there 
 * will be some optional tutorials for this purpose.
 */

#include <stdio.h>
#include <unistd.h>

int main ( void )
{
   /* Note that you will need to create these files! Put 
      some configuration data (of your choice!) in settings.conf. */
   static const char cfilename[] = "settings.conf"; 
   static const char lfilename[] = "activity.log";
   FILE *config = fopen ( cfilename, "r" );
   FILE *log = fopen ( lfilename, "w" );
   char str[] = "Activity Log:\n";

   if ( config != NULL )
   {
      char line [ 255 ]; /* or other suitable maximum line size */
      printf("Starting with the following configuration: \n");

      while ( fgets ( line, sizeof line, config ) != NULL ) /* read a line */
      {
         fputs ( line, stdout ); /* write the line */
      }
      fclose ( config );
	
      if ( log != NULL)
      {
         fwrite( str, 1, sizeof(str)-1, log);

	 /* Here you can imagine all sorts of other things happen
 	    with the custom application, but I'm being easy on you
 	    since this is already difficult enough :) */

         fclose ( log );
      } 
      else 
      {
         perror ( lfilename ); /* why didn't the file open? */
      }
   }
   else
   {
      perror ( cfilename ); /* why didn't the file open? */
   }
   sleep(60); /* This gives you a minute to verify the SELinux domain by typing ps -auZ */
   return 0;
}

