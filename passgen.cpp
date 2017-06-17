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

int main(int argc, char **argv)
{
  FILE *fp;
  fp = fopen("password.txt", "w+");
  char buff[BUFF_LEN];
  int buff_i = 0;
  char valid_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*";
  int n_valid_chars = strlen(valid_chars);
  char *og_password_0[] = { "ыфтфтвкуфы" };
  int n_og_password_0 = 1;
  //char *og_password_1[] = {"", "96","1996","1492","1942","1608","25050602","1803","3103","0110"};
  //int n_og_password_1 = 10;
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

  char *og_password_2[] = { "", "вфтсрук", "вщшесщьу", "вугымгде" };
  int n_og_password_2 = 4;


/*
ыфтфтвкуфы96
ыфтфтвкуфы96вфтсрук
ыфтфтвкуфы96вщшесщьу
ыфтфтвкуфы96вугымгде
*/

  /*
  ыфтфтвкуфы = sanandreas?
  вфтсрук = dancher?
  вщшесщьу = ddoitcome
  */

  int og_password_len_0[n_og_password_0];
  for(int i = 0; i < n_og_password_0; i++)
    og_password_len_0[i]= strlen(og_password_0[i]);
  int og_password_len_1[n_og_password_1];
  for(int i = 0; i < n_og_password_1; i++)
    og_password_len_1[i]= strlen(og_password_1[i]);
  int og_password_len_2[n_og_password_2];
  for(int i = 0; i < n_og_password_2; i++)
    og_password_len_2[i]= strlen(og_password_2[i]);

  char og_password[300]; //gets populated with every permutation of og_password_0og_password_1og_password_2
  int og_password_len;
  char new_password[300];

  int cur_password_i = 0;
  int cur_password_ii = 0;
  int cur_char_i = 0;
  int cur_char_ii = 0;
  int done = 0;

  int fully_done = 0;
  int cur_og_password_0 = 0;
  int cur_og_password_1 = 0;
  int cur_og_password_2 = 0;

  while(!fully_done)
  {
    strcpy(og_password,                                                                          og_password_0[cur_og_password_0]);
    strcpy(og_password+og_password_len_0[cur_og_password_0],                                     og_password_1[cur_og_password_1]);
    strcpy(og_password+og_password_len_0[cur_og_password_0]+og_password_len_1[cur_og_password_1],og_password_2[cur_og_password_2]);
    og_password[       og_password_len_0[cur_og_password_0]+og_password_len_1[cur_og_password_1]+og_password_len_2[cur_og_password_2]] = '\0';
    og_password_len = strlen(og_password);

    strcpy(new_password,og_password);
    new_password[og_password_len] = '\n';
    new_password[og_password_len+1] = '\0';
    buff_i = appendPassword(new_password, buff, buff_i, fp);

/*
    //try deletion
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

    //try substitution
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

    //try injection
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

    //try double substitution
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

    //try substitution injection
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
    */

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

  fwrite(buff,sizeof(char),buff_i,fp);
  fclose(fp);
}

