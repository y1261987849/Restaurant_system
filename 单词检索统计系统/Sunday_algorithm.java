package com.source;

public class Sunday_algorithm
{
    public static int count(String str_Total, String str_Pattern)
    {
        if (str_Total == null || str_Pattern == null)
            return 0;

        /*
        if (str_Total.length() < str_Pattern.length())
            return -1;
         */

        char charTotal [] = str_Total.toCharArray();
        char charSearch [] = str_Pattern.toCharArray();

        int t = 0;
        int s = 0;
        int existCount = 0;
        while(s < charSearch.length && t < charTotal.length) {

            if(charSearch[s] == charTotal[t]) {

                if((s + 1) != charSearch.length) {
                    s++;
                    t++;
                }else {
                    existCount++;
                    if(charTotal.length - (t + 1) >= charSearch.length) {
                        s = 0;
                        t++;
                    }else {
                        break;
                    }
                }
            }else {
                int num = t + charSearch.length;
                int index = -1;
                if(num < charTotal.length) {

                    for(int i = 0; i < charSearch.length; i++) {
                        if(charTotal[num] == charSearch[i]) {
                            index = i;
                            break;
                        }
                    }
                    if(index != -1) {
                        t = t + (charSearch.length - index);
                        s = 0;

                    }else {
                        t = num + 1;
                        s = 0;
                    }
                }else {
                    break;
                }
            }
            if(t >= charTotal.length) {
                break;
            }
        }
        return existCount;
    }

    public static int search(String str_Total, String str_Pattern)
    {
        if (str_Total == null || str_Pattern == null) {
            return 0;
        }
        if (str_Total.length() < str_Pattern.length()) {
            return -1;
        }

        int totalIndex = 0;
        int patternIndex = 0;
        while (totalIndex < str_Pattern.length()) {
            if (totalIndex > str_Total.length() - 1) {
                return -1;
            }
            if (str_Total.charAt(totalIndex) == str_Pattern.charAt(patternIndex)) {
                totalIndex++;
                patternIndex++;
            } else {
                int nextCharIndex = totalIndex - patternIndex + str_Pattern.length();
                if (nextCharIndex < str_Total.length()) {
                    int step = str_Pattern.lastIndexOf(str_Total.charAt(nextCharIndex));
                    if (step == -1) {
                        totalIndex = nextCharIndex + 1;
                    } else {
                        totalIndex = nextCharIndex - step;
                    }
                    patternIndex = 0;
                } else {
                    return -1;
                }
            }
        }
        return totalIndex - patternIndex;
    }
}
