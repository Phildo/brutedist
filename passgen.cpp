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
    case 'g': c = "G9"; break;
    case 'h': c = "H"; break;
    case 'i': c = "I!1"; break;
    case 'j': c = "J"; break;
    case 'k': c = "K"; break;
    case 'l': c = "L!Ii71"; break;
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
    case 'z': c = "Z2"; break;
    case 'A': c = "a4"; break;
    case 'B': c = "b"; break;
    case 'C': c = "c"; break;
    case 'D': c = "d"; break;
    case 'E': c = "e3"; break;
    case 'F': c = "f"; break;
    case 'G': c = "g9"; break;
    case 'H': c = "h"; break;
    case 'I': c = "i!1"; break;
    case 'J': c = "j"; break;
    case 'K': c = "k"; break;
    case 'L': c = "l!Ii71"; break;
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
    case 'Z': c = "z2"; break;
    case '0': c = "oO"; break;
    case '1': c = "Ii!"; break;
    case '2': c = "zZ"; break;
    case '3': c = "eE"; break;
    case '4': c = "Aa"; break;
    case '5': c = "Ss"; break;
    case '6': c = ""; break;
    case '7': c = "Ll"; break;
    case '8': c = ""; break;
    case '9': c = "g"; break;
    default: c = ""; break;
  }
  return c[i];
}

int find_valid_delete(int i, char *s, int *ri)
{
  if(s[i] == '\0' || s[i] == '\n')
    return 0;
  return 1;
}

void basic_delete(int i, char *s)
{
  for(int j = i; s[j] != '\0'; j++)
    s[j] = s[j+1];
}

int find_valid_smart_substitution(int i, int sub_i, char *s, int *ri, int *rsub_i)
{
  if(s[i] == '\0' || s[i] == '\n')
    return 0;
  char sub_char = smart_sub(sub_i, s[i]);
  while(sub_char == '\0')
  {
    sub_i = 0;
    i++;
    if(s[i] == '\0' || s[i] == '\n')
      return 0;
    else
      sub_char = smart_sub(sub_i, s[i]);
  }
  *ri = i;
  *rsub_i = sub_i;
  return 1;
}

void basic_smart_substitute(int i, int sub_i, char *s)
{
  s[i] = smart_sub(sub_i, s[i]);
}

int find_valid_substitution(int i, char *set, int set_i, char *s, int *ri, int *rset_i)
{
  if(s[i] == '\0' || s[i] == '\n')
    return 0;
  if(set[set_i] == '\0')
  {
    set_i = 0;
    i++;
    if(s[i] == '\0' || s[i] == '\n')
      return 0;
  }
  *ri = i;
  *rset_i = set_i;
  return 1;
}

void basic_substitute(int i, char *set, int set_i, char *s)
{
  s[i] = set[set_i];
}

int find_valid_inject(int i, char *set, int set_i, char *s, int *ri, int *rset_i)
{
  if(set[set_i] == '\0')
  {
    set_i = 0;
    i++;
    if(s[i-1] == '\0' || s[i-1] == '\n')
      return 0;
  }
  *ri = i;
  *rset_i = set_i;
  return 1;
}

void basic_inject(int i, char *set, int set_i, char *s)
{
  char tmp = s[i];
  char newtmp;
  for(int j = i; s[j] != '\0'; j++)
  {
    newtmp = s[j+1];
    s[j+1] = tmp;
    tmp = newtmp;
  }
  s[i] = set[set_i];
}

int main(int argc, char **argv)
{
  int try_deletion                  = 1;
  int try_smart_substitution        = 0;
  int try_substitution              = 1;
  int try_injection                 = 1;
  int try_double_smart_substitution = 1;
  int try_double_substitution       = 0;
  int try_double_injection          = 0;
  int try_substitution_injection    = 0;
  int try_triple_smart_substitution = 1;

  FILE *fp;
  fp = fopen("password.txt", "w+");
  char buff[BUFF_LEN];
  int buff_i = 0;
  char valid_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!";
  int n_valid_chars = strlen(valid_chars);

  char *og_password_0[] = { "test" };
  int n_og_password_0 = 1;
  char *og_password_1[] = { "" };
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
  char tmp_og_password[300]; //used for recursion
  int tmp_og_password_len;
  char tmp_tmp_og_password[300]; //used for double recursion
  int tmp_tmp_og_password_len;
  char new_password[300];

  int cur_password_i = 0;
  int cur_password_ii = 0;
  int cur_password_iii = 0;
  int cur_char_i = 0;
  int cur_char_ii = 0;
  int cur_char_iii = 0;
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
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        basic_delete(cur_password_i, new_password);
        buff_i = appendPassword(new_password, buff, buff_i, fp);

        cur_password_i++;
        done = !find_valid_delete(cur_password_i, og_password, &cur_password_i);
      }
    }

    //try smart substitution
    if(try_smart_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = !find_valid_smart_substitution(cur_password_i, cur_char_i, og_password, &cur_password_i, &cur_char_i);
      while(!done)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        basic_smart_substitute(cur_password_i, cur_char_i, new_password);
        buff_i = appendPassword(new_password, buff, buff_i, fp);

        cur_char_i++;
        done = !find_valid_smart_substitution(cur_password_i, cur_char_i, og_password, &cur_password_i, &cur_char_i);
      }
    }

    //try substitution
    if(try_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = 0;
      while(!done)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        basic_substitute(cur_password_i, valid_chars, cur_char_i, new_password);
        buff_i = appendPassword(new_password, buff, buff_i, fp);

        cur_char_i++;
        done = !find_valid_substitution(cur_password_i, valid_chars, cur_char_i, og_password, &cur_password_i, &cur_char_i);
      }
    }

    //try injection
    if(try_injection)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = 0;
      while(!done)
      {
        strcpy(new_password,og_password);
        new_password[og_password_len] = '\n';
        new_password[og_password_len+1] = '\0';

        basic_inject(cur_password_i, valid_chars, cur_char_i, new_password);
        buff_i = appendPassword(new_password, buff, buff_i, fp);

        cur_char_i++;
        done = !find_valid_inject(cur_password_i, valid_chars, cur_char_i, og_password, &cur_password_i, &cur_char_i);
      }
    }

    //try double smart substitution
    if(try_double_smart_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = !find_valid_smart_substitution(cur_password_i, cur_char_i, og_password, &cur_password_i, &cur_char_i);
      while(!done)
      {
        strcpy(tmp_og_password,og_password);
        basic_smart_substitute(cur_password_i, cur_char_i, tmp_og_password);

        cur_password_ii = cur_password_i+1;
        cur_char_ii = 0;
        done = !find_valid_smart_substitution(cur_password_ii, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
        while(!done)
        {
          strcpy(new_password,tmp_og_password);
          new_password[og_password_len] = '\n';
          new_password[og_password_len+1] = '\0';

          basic_smart_substitute(cur_password_ii, cur_char_ii, new_password);
          buff_i = appendPassword(new_password, buff, buff_i, fp);

          cur_char_ii++;
          done = !find_valid_smart_substitution(cur_password_ii, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
          while(!done && cur_password_ii == cur_password_i)
          {
            cur_char_ii++;
            done = !find_valid_smart_substitution(cur_password_ii, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
          }
        }

        cur_char_i++;
        done = !find_valid_smart_substitution(cur_password_i, cur_char_i, og_password, &cur_password_i, &cur_char_i);
      }
    }

    //try double substitution
    if(try_double_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = 0;
      while(!done)
      {
        strcpy(tmp_og_password,og_password);
        basic_substitute(cur_password_i, valid_chars, cur_char_i, tmp_og_password);

        cur_password_ii = cur_password_i+1;
        cur_char_ii = 0;
        done = !find_valid_substitution(cur_password_ii, valid_chars, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
        while(!done)
        {
          strcpy(new_password,tmp_og_password);
          new_password[og_password_len] = '\n';
          new_password[og_password_len+1] = '\0';

          basic_substitute(cur_password_ii, valid_chars, cur_char_ii, new_password);
          buff_i = appendPassword(new_password, buff, buff_i, fp);

          cur_char_ii++;
          done = !find_valid_substitution(cur_password_ii, valid_chars, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
          while(!done && cur_password_ii == cur_password_i)
          {
            cur_char_ii++;
            done = !find_valid_substitution(cur_password_ii, valid_chars, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
          }
        }

        cur_char_i++;
        done = !find_valid_substitution(cur_password_i, valid_chars, cur_char_i, og_password, &cur_password_i, &cur_char_i);
      }
    }

    //try double injection
    if(try_double_injection)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = 0;
      while(!done)
      {
        strcpy(tmp_og_password,og_password);
        basic_inject(cur_password_i, valid_chars, cur_char_i, tmp_og_password);

        cur_password_ii = 0;
        cur_char_ii = 0;
        done = !find_valid_inject(cur_password_ii, valid_chars, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
        while(!done && cur_password_ii == cur_password_i)
        {
          cur_char_ii++;
          done = !find_valid_inject(cur_password_ii, valid_chars, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
        }
        while(!done)
        {
          strcpy(new_password,tmp_og_password);
          new_password[og_password_len+1] = '\n';
          new_password[og_password_len+2] = '\0';

          basic_inject(cur_password_ii, valid_chars, cur_char_ii, new_password);
          buff_i = appendPassword(new_password, buff, buff_i, fp);

          cur_char_ii++;
          done = !find_valid_inject(cur_password_ii, valid_chars, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
          while(!done && cur_password_ii == cur_password_i)
          {
            cur_char_ii++;
            done = !find_valid_inject(cur_password_ii, valid_chars, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
          }
        }

        cur_char_i++;
        done = !find_valid_inject(cur_password_i, valid_chars, cur_char_i, og_password, &cur_password_i, &cur_char_i);
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

    //try triple smart substitution
    if(try_triple_smart_substitution)
    {
      cur_password_i = 0;
      cur_char_i = 0;
      done = !find_valid_smart_substitution(cur_password_i, cur_char_i, og_password, &cur_password_i, &cur_char_i);
      while(!done)
      {
        strcpy(tmp_og_password,og_password);
        basic_smart_substitute(cur_password_i, cur_char_i, tmp_og_password);

        cur_password_ii = cur_password_i+1;
        cur_char_ii = 0;
        done = !find_valid_smart_substitution(cur_password_ii, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
        while(!done)
        {
          strcpy(tmp_tmp_og_password,tmp_og_password);
          basic_smart_substitute(cur_password_ii, cur_char_ii, tmp_tmp_og_password);

          cur_password_iii = cur_password_ii+1;
          cur_char_iii = 0;
          done = !find_valid_smart_substitution(cur_password_iii, cur_char_iii, tmp_tmp_og_password, &cur_password_iii, &cur_char_iii);
          while(!done)
          {
            strcpy(new_password,tmp_tmp_og_password);
            new_password[og_password_len] = '\n';
            new_password[og_password_len+1] = '\0';

            basic_smart_substitute(cur_password_iii, cur_char_iii, new_password);
            buff_i = appendPassword(new_password, buff, buff_i, fp);

            cur_char_iii++;
            done = !find_valid_smart_substitution(cur_password_iii, cur_char_iii, tmp_tmp_og_password, &cur_password_iii, &cur_char_iii);
            while(!done && cur_password_iii == cur_password_ii)
            {
              cur_char_iii++;
              done = !find_valid_smart_substitution(cur_password_iii, cur_char_iii, tmp_tmp_og_password, &cur_password_iii, &cur_char_iii);
            }
          }

          cur_char_ii++;
          done = !find_valid_smart_substitution(cur_password_ii, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
          while(!done && cur_password_ii == cur_password_i)
          {
            cur_char_ii++;
            done = !find_valid_smart_substitution(cur_password_ii, cur_char_ii, tmp_og_password, &cur_password_ii, &cur_char_ii);
          }
        }

        cur_char_i++;
        done = !find_valid_smart_substitution(cur_password_i, cur_char_i, og_password, &cur_password_i, &cur_char_i);
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

