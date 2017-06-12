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
      char valid_chars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()<>.,[]";
      int n_valid_chars = strlen(valid_chars);
      char og_password[] = "xyz134xmNTSR1347gYZTf#!?";
      int password_len = strlen(og_password);
      char new_password[200];
    
      int cur_password_i = 0;
      int cur_password_ii = 0;
      int cur_char_i = 0;
      int cur_char_ii = 0;
    
      int attempt_start_i = 0;
      int attempt_end_i = 1000000;

      int substitution_attempts = password_len*n_valid_chars;
      int injection_attempts = (password_len+1)*n_valid_chars;
      int double_substitution_attempts = password_len*n_valid_chars*(password_len-1)*n_valid_chars;
      for(int i = attempt_start_i; i < attempt_end_i; i++)
      {
        strcpy(new_password,og_password);
        new_password[password_len] = '\n';
        new_password[password_len+1] = '\0';
        if(i < substitution_attempts) //try substitution
        {
          new_password[cur_password_i] = valid_chars[cur_char_i];
          cur_char_i++;
          if(cur_char_i >= n_valid_chars)
          {
            cur_char_i = 0;
            cur_password_i++;
            if(cur_password_i >= password_len)
              cur_password_i = 0;
          }
          buff_i = appendPassword(new_password, buff, buff_i, fp);
        }
        else if(i < substitution_attempts+injection_attempts) //try injection
        {
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
            if(cur_password_i >= password_len+1)
              cur_password_i = 0;
          }
          buff_i = appendPassword(new_password, buff, buff_i, fp);
        }
        else if(i < substitution_attempts+injection_attempts+double_substitution_attempts) //try double injection
        {
          new_password[cur_password_i] = valid_chars[cur_char_i];
          new_password[cur_password_ii] = valid_chars[cur_char_ii];

          cur_char_ii++;
          if(cur_char_i == cur_char_ii) cur_char_ii++;

          if(cur_char_ii >= n_valid_chars)
          {
            cur_char_ii = 0;
            cur_password_ii++;
            if(cur_password_ii >= password_len)
            {
              cur_password_ii = 0;
              cur_char_i++;
              if(cur_char_i >= n_valid_chars)
              {
                cur_char_i = 0;
                cur_password_i++;
                if(cur_password_i >= password_len)
                  cur_password_i = 0;
              }
            }
          }

          buff_i = appendPassword(new_password, buff, buff_i, fp);
        }
      }
      fwrite(buff,sizeof(char),buff_i,fp);
      fclose(fp);
    }
