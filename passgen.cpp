#include "stdio.h"
#include "stdlib.h"
#include "string.h"

//1MB
#define BUFF_LEN 1024*1024

int appendPassword(char *pass, char *buff, int buff_i, FILE *fp) //pass must end in \n\0
{
  int pass_i = 0;
  while(buff_i < BUFF_LEN && pass[pass_i] != '\0')
  {
    buff[buff_i] = pass[pass_i];
    buff_i++;
    pass_i++;
  }
  if(buff_i >= BUFF_LEN)
  {
    fwrite(buff,sizeof(char),BUFF_LEN,fp);
    buff_i = 0;
  }
  while(buff_i < BUFF_LEN && pass[pass_i] != '\0')
  {
    buff[buff_i] = pass[pass_i];
    buff_i++;
    pass_i++;
  }
  return buff_i;
}

char smart_sub(int i, char key)
{
  char *c;
  switch(key)
  {
    case 'a': c = "A4"; break;
    case 'b': c = "B"; break;
    case 'c': c = "C"; break;
    case 'd': c = "D"; break;
    case 'e': c = "E3"; break;
    case 'f': c = "F"; break;
    case 'g': c = "G"; break;
    case 'h': c = "H"; break;
    case 'i': c = "I!"; break;
    case 'j': c = "J"; break;
    case 'k': c = "K"; break;
    case 'l': c = "L!Ii"; break;
    case 'm': c = "M"; break;
    case 'n': c = "N"; break;
    case 'o': c = "O0"; break;
    case 'p': c = "P"; break;
    case 'q': c = "Q"; break;
    case 'r': c = "R"; break;
    case 's': c = "S5"; break;
    case 't': c = "T"; break;
    case 'u': c = "U"; break;
    case 'v': c = "V"; break;
    case 'w': c = "W"; break;
    case 'x': c = "X"; break;
    case 'y': c = "Y"; break;
    case 'z': c = "Z"; break;
    case 'A': c = "a4"; break;
    case 'B': c = "b"; break;
    case 'C': c = "c"; break;
    case 'D': c = "d"; break;
    case 'E': c = "e3"; break;
    case 'F': c = "f"; break;
    case 'G': c = "g"; break;
    case 'H': c = "h"; break;
    case 'I': c = "i!"; break;
    case 'J': c = "j"; break;
    case 'K': c = "k"; break;
    case 'L': c = "l!Ii"; break;
    case 'M': c = "m"; break;
    case 'N': c = "n"; break;
    case 'O': c = "o0"; break;
    case 'P': c = "p"; break;
    case 'Q': c = "q"; break;
    case 'R': c = "r"; break;
    case 'S': c = "s5"; break;
    case 'T': c = "t"; break;
    case 'U': c = "u"; break;
    case 'V': c = "v"; break;
    case 'W': c = "w"; break;
    case 'X': c = "x"; break;
    case 'Y': c = "y"; break;
    case 'Z': c = "z"; break;
    case '0': c = "oO"; break;
    case '1': c = "i!"; break;
    case '2': c = "zZ"; break;
    case '3': c = "eE"; break;
    case '4': c = "A"; break;
    case '5': c = "Ss"; break;
    case '6': c = ""; break;
    case '7': c = "L"; break;
    case '8': c = ""; break;
    case '9': c = ""; break;
    default: c = ""; break;
  }
  return c[i];
}

int main(int argc, char **argv)
{
  int try_deletion                  = 0;
  int try_smart_substitution        = 1;
  int try_substitution              = 0;
  int try_injection                 = 0;
  int try_double_smart_substitution = 1;
  int try_double_substitution       = 0;
  int try_substitution_injection    = 0;

  FILE *fp;
  fp = fopen("password.txt", "w+");
  char buff[BUFF_LEN];
  int buff_i = 0;
  char valid_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!";
  int n_valid_chars = strlen(valid_chars);
  char *og_password_0[] = { "test" };
  int n_og_password_0 = 1;
  char *og_password_1[] = {""};
  int n_og_password_1 = 1;

  /*
  //populate n_og_password_1 with all combinations of 0-4 digit numbers
  int n_og_password_1 = 11111;
  char *og_password_1_content = (char *)malloc(sizeof(char)*5*11111);
  char **og_password_1 = (char **)malloc(sizeof(char *)*11111);
  int v;
  for(int i = 0; i < n_og_password_1; i++)
  {
    if(i < 1)
    {
      og_password_1_content[i*5+0] = '\0';
    }
    else if(i < 11)
    {
      v = i-1;
      og_password_1_content[i*5+1] = '\0';
      og_password_1_content[i*5+0] = '0'+v;
    }
    else if(i < 111)
    {
      v = i-11;
      og_password_1_content[i*5+2] = '\0';
      og_password_1_content[i*5+1] = '0'+(v%10);
      og_password_1_content[i*5+0] = '0'+(v/10);
    }
    else if(i < 1111)
    {
      v = i-111;
      og_password_1_content[i*5+3] = '\0';
      og_password_1_content[i*5+2] = '0'+(v%10);
      og_password_1_content[i*5+1] = '0'+(v/10)%10;
      og_password_1_content[i*5+0] = '0'+(v/100);
    }
    else if(i < 11111)
    {
      v = i-1111;
      og_password_1_content[i*5+4] = '\0';
      og_password_1_content[i*5+3] = '0'+(v%10);
      og_password_1_content[i*5+2] = '0'+(v/10)%10;
      og_password_1_content[i*5+1] = '0'+(v/100)%10;
      og_password_1_content[i*5+0] = '0'+(v/1000)%10;
    }
    og_password_1[i] = og_password_1_content+(i*5);
  }
  */

  char *og_password_2[] = { "" };
  int n_og_password_2 = 1;

  char *og_password_3[] = { "" };
  int n_og_password_3 = 1;

  int og_password_len_0[n_og_password_0];
  for(int i = 0; i < n_og_password_0; i++)
    og_password_len_0[i]= strlen(og_password_0[i]);
  int og_password_len_1[n_og_password_1];
  for(int i = 0; i < n_og_password_1; i++)
    og_password_len_1[i]= strlen(og_password_1[i]);
  int og_password_len_2[n_og_password_2];
  for(int i = 0; i < n_og_password_2; i++)
    og_password_len_2[i]= strlen(og_password_2[i]);
  int og_password_len_3[n_og_password_3];
  for(int i = 0; i < n_og_password_3; i++)
    og_password_len_3[i]= strlen(og_password_3[i]);

  char og_password[300]; //gets populated with every permutation of og_password_0og_password_1og_password_2og_password_3
  int og_password_len;
  char new_password[300];

  int cur_password_i = 0;
  int cur_password_ii = 0;
  int cur_char_i = 0;
  int cur_char_ii = 0;
  char sub_i;
  char old_i;
  char sub_ii;
  char old_ii;
  int done = 0;

  int fully_done = 0;
  int cur_og_password_0 = 0;
  int cur_og_password_1 = 0;
  int cur_og_password_2 = 0;
  int cur_og_password_3 = 0;

  while(!fully_done)
  {
    strcpy(og_password,                                                                                                               og_password_0[cur_og_password_0]);
    strcpy(og_password+og_password_len_0[cur_og_password_0],                                                                          og_password_1[cur_og_password_1]);
    strcpy(og_password+og_password_len_0[cur_og_password_0]+og_password_len_1[cur_og_password_1],                                     og_password_2[cur_og_password_2]);
    strcpy(og_password+og_password_len_0[cur_og_password_0]+og_password_len_1[cur_og_password_1]+og_password_len_2[cur_og_password_2],og_password_3[cur_og_password_3]);
    og_password[       og_password_len_0[cur_og_password_0]+og_password_len_1[cur_og_password_1]+og_password_len_2[cur_og_password_2]+og_password_len_3[cur_og_password_3]] = '\0';
    og_password_len = strlen(og_password);

    strcpy(new_password,og_password);
    new_password[og_password_len] = '\n';
    new_password[og_password_len+1] = '\0';
    buff_i = appendPassword(new_password, buff, buff_i, fp);

    //try deletion
    if(try_deletion)
    {
      cur_password_i = 0;
      done = 0;
      while(!done)
      //for(int i = 0; i < deletion_attempts; i++)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        for(int j = cur_password_i; new_password[j] != '\0'; j++)
          new_password[j] = new_password[j+1];
        cur_password_i++;
        if(cur_password_i >= og_password_len)
          done = 1;

        buff_i = appendPassword(new_password, buff, buff_i, fp);
      }
    }

    //try smart substitution
    if(try_smart_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = 0;
      //pre populate with valid positions
      sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
      while(sub_i == '\0' && !done)
      {
        cur_char_i = 0;
        cur_password_i++;
        if(cur_password_i >= og_password_len)
          done = 1;
        else
          sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
      }
      while(!done)
      //for(int i = 0; i < substitution_attempts; i++)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
        old_i = new_password[cur_password_i];
        new_password[cur_password_i] = sub_i;
        buff_i = appendPassword(new_password, buff, buff_i, fp);
        new_password[cur_password_i] = old_i;

        cur_char_i++;
        sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
        while(sub_i == '\0' && !done)
        {
          cur_char_i = 0;
          cur_password_i++;
          if(cur_password_i >= og_password_len)
            done = 1;
          else
            sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
        }
      }
    }

    //try substitution
    if(try_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = 0;
      while(!done)
      //for(int i = 0; i < substitution_attempts; i++)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        new_password[cur_password_i] = valid_chars[cur_char_i];
        cur_char_i++;
        if(cur_char_i >= n_valid_chars)
        {
          cur_char_i = 0;
          cur_password_i++;
          if(cur_password_i >= og_password_len)
            done = 1;
        }
        buff_i = appendPassword(new_password, buff, buff_i, fp);
      }
    }

    //try injection
    if(try_injection)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = 0;
      while(!done)
      //for(int i = 0; i < injection_attempts; i++)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        char tmp = new_password[cur_password_i];
        char newtmp;
        for(int j = cur_password_i; new_password[j] != '\0'; j++)
        {
          newtmp = new_password[j+1];
          new_password[j+1] = tmp;
          tmp = newtmp;
        }
        new_password[cur_password_i] = valid_chars[cur_char_i];
        cur_char_i++;
        if(cur_char_i >= n_valid_chars)
        {
          cur_char_i = 0;
          cur_password_i++;
          if(cur_password_i >= og_password_len+1)
            done = 1;
        }
        buff_i = appendPassword(new_password, buff, buff_i, fp);
      }
    }

    //try double smart substitution
    if(try_double_smart_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      cur_password_ii = 0;
      cur_char_ii = 0;
      done = 0;
      //pre populate with valid first position
      sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
      while(sub_i == '\0' && !done)
      {
        cur_char_i = 0;
        cur_password_i++;
        if(cur_password_i >= og_password_len)
          done = 1;
        else
          sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
      }
      //pre populate with valid second position
      cur_password_ii = cur_password_i+1;
      sub_ii = smart_sub(cur_char_ii, new_password[cur_password_ii]);
      while(sub_ii == '\0' && !done)
      {
        cur_char_ii = 0;
        cur_password_ii++;
        if(cur_password_ii >= og_password_len)
          done = 1;
        else
          sub_ii = smart_sub(cur_char_ii, new_password[cur_password_ii]);
      }
      while(!done)
      //for(int i = 0; i < substitution_attempts; i++)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
        old_i = new_password[cur_password_i];
        new_password[cur_password_i] = sub_i;
        sub_ii = smart_sub(cur_char_ii, new_password[cur_password_ii]);
        old_ii = new_password[cur_password_ii];
        new_password[cur_password_ii] = sub_ii;
        buff_i = appendPassword(new_password, buff, buff_i, fp);
        new_password[cur_password_i] = old_i;
        new_password[cur_password_ii] = old_ii;

        cur_char_ii++;
        sub_ii = smart_sub(cur_char_ii, new_password[cur_password_ii]);
        while(sub_ii == '\0' && !done)
        {
          cur_char_ii = 0;
          cur_password_ii++;
          if(cur_password_ii == cur_password_i) cur_password_ii++;
          if(cur_password_ii >= og_password_len)
          {

            //increment _i
            cur_char_i++;
            sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
            while(sub_i == '\0' && !done)
            {
              cur_char_i = 0;
              cur_password_i++;
              if(cur_password_i >= og_password_len)
                done = 1;
              else
                sub_i = smart_sub(cur_char_i, new_password[cur_password_i]);
            }

            //increment _ii to valid, non_i spot
            cur_password_ii = 0;
            if(cur_password_ii == cur_password_i) cur_password_ii++;
            cur_char_ii = 0;
            sub_ii = smart_sub(cur_char_ii, new_password[cur_password_ii]);
            while(sub_ii == '\0' && !done)
            {
              cur_char_ii = 0;
              cur_password_ii++;
              if(cur_password_ii == cur_password_i) cur_password_ii++;
              if(cur_password_ii >= og_password_len)
                done = 1;
              else
                sub_ii = smart_sub(cur_char_i, new_password[cur_password_i]);
            }

          }
          else
            sub_ii = smart_sub(cur_char_i, new_password[cur_password_i]);
        }
      }
    }

    //try double substitution
    if(try_double_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      cur_password_ii = 1;
      cur_char_ii = 0;
      done = 0;
      while(!done)
      //for(int i = 0; i < double_substitution_attempts; i++)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        new_password[cur_password_i] = valid_chars[cur_char_i];
        new_password[cur_password_ii] = valid_chars[cur_char_ii];

        cur_char_ii++;

        if(cur_char_ii >= n_valid_chars)
        {
          cur_char_ii = 0;
          cur_password_ii++;
          if(cur_password_i == cur_password_ii) cur_password_ii++;
          if(cur_password_ii >= og_password_len)
          {
            cur_password_ii = 0;
            if(cur_password_i == cur_password_ii) cur_password_ii++;
            cur_char_i++;
            if(cur_char_i >= n_valid_chars)
            {
              cur_char_i = 0;
              cur_password_i++;
              if(cur_password_i >= og_password_len)
                done = 1;
            }
          }
        }

        buff_i = appendPassword(new_password, buff, buff_i, fp);
      }
    }

    //try substitution injection
    if(try_substitution_injection)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      cur_password_ii = 1;
      cur_char_ii = 0;
      done = 0;
      while(!done)
      //for(int i = 0; i < substitution_injection_attempts; i++)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        new_password[cur_password_i] = valid_chars[cur_char_i];

        char tmp = new_password[cur_password_ii];
        char newtmp;
        for(int j = cur_password_ii; new_password[j] != '\0'; j++)
        {
          newtmp = new_password[j+1];
          new_password[j+1] = tmp;
          tmp = newtmp;
        }
        new_password[cur_password_ii] = valid_chars[cur_char_ii];
        cur_char_ii++;
        if(cur_char_ii >= n_valid_chars)
        {
          cur_char_ii = 0;
          cur_password_ii++;
          if(cur_password_ii >= og_password_len+1)
          {
            cur_password_ii = 0;
            cur_char_i++;
            if(cur_char_i >= n_valid_chars)
            {
              cur_char_i = 0;
              cur_password_i++;
              if(cur_password_i >= og_password_len)
                done = 1;
            }
          }
        }
        buff_i = appendPassword(new_password, buff, buff_i, fp);
      }
    }

    //basic combinatorics
    cur_og_password_3++;
    if(cur_og_password_3 >= n_og_password_3)
    {
      cur_og_password_3 = 0;
      cur_og_password_2++;
      if(cur_og_password_2 >= n_og_password_2)
      {
        cur_og_password_2 = 0;
        cur_og_password_1++;
        if(cur_og_password_1 >= n_og_password_1)
        {
          cur_og_password_1 = 0;
          cur_og_password_0++;
          if(cur_og_password_0 >= n_og_password_0) fully_done = 1;
        }
      }
    }

  }

  fwrite(buff,sizeof(char),buff_i,fp);
  fclose(fp);
}

