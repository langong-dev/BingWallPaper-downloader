#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

string getshell(string cmd)
{
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");
    stream = popen(cmd.c_str(), "r");
    if (stream)
    {
        while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    return data;
}

int main ()
{
    char url[200];
    int j = 0;
    system ("wget -O tmp \"http://www.bing.com/HPImageArchive.aspx?format=js&idx=0&n=1&mkt=en-US\" && clear");
    string text = getshell("cat ./tmp");
    system ("rm ./tmp");
    for (int i = 0; i < 500; i++)
    {
        if (text[i] == 'u' && text[i+1] == 'r' && text[i+2] == 'l')// url":"
        {
            while (text[i] != '&')
            {
                url[j] = text[i+6];
                j++;
                i++;
            }
            goto get;
        }
    }
    get:

        cout << text << endl;
        cout << "====================================================================\n";
        char c[100] = "wget cn.bing.com";
        strcat (c, url);
        system (c);
    return 0;
}

