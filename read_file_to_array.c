    FILE * fp;
    long len;
    
   fp = fopen ("xxxxxx", "r");
    if(fp == NULL)
    {
        return -1;
    }
    fseek(fp,0,SEEK_END);
    len = ftell(fp);
    fseek(fp,0,SEEK_SET);
    char arr[len] = {0};
    int i = 0;
    while(1){
        char ch =  getc(fp);
        if(ch == EOF)
        {
            break;
        }
        arr[i] = ch;
        i++; 
    }
