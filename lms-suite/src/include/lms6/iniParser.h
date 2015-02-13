/**
@file   iniParser.h
@author Lime Microsystems (www.limemicro.com)
@brief  Class for parsing config files
*/

#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <map>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <string.h>
using namespace std;
namespace lms6
{
class iniParser
{
public:
    iniParser()
    {
        m_currentFilename = "";
        m_currentSectionName = "";
    }
    ~iniParser(){};

    bool ParseArray(const char *buffer)
    {
        stringstream fin;
        fin.str(buffer);
        const int bufSize = 512;
        m_currentFilename = "ParsedBuffer.txt";

        char cline[bufSize];
        memset(cline, 0, bufSize);
        char *poss = 0;
        char *pose = 0;

        char key[bufSize/2];
        char value[bufSize/2];

        bool sectionDetected = false;

        while(!fin.eof())
        {
            if(!sectionDetected)
            {
                memset(cline, 0, bufSize);
                fin.getline(cline, bufSize-1);
                sectionDetected = false;
            }
            poss = strstr(cline, "[");
            pose = strstr(cline, "]");
            if( poss != NULL && pose != NULL) //section detected
            {
                sectionDetected = false;
                char secName[bufSize];
                memset(secName, 0, bufSize);
                strncpy(secName, poss+1, pose-poss-1);
                SelectSection(secName);
                while(!fin.eof())
                {
                    memset(cline, 0, bufSize);
                    memset(key, 0, bufSize/2);
                    memset(value, 0, bufSize/2);
                    fin.getline(cline, bufSize-1);
                    if( strlen(cline) == 0)
                        continue; //skip empty lines

                    if( strstr(cline, "[") != NULL )
                    {
                        sectionDetected = true;
                        break; // next section detected
                    }

                    poss = cline;
                    pose = strstr(cline, "=");
                    if(pose == NULL)
                    {
                        //continue; //no value pair found
                        pose = poss+strlen(poss);
                    }
                    //copy key value
                    memset(key, 0, bufSize/2);
                    strncpy(key, poss, pose-poss);

                    poss = pose+1;
                    if(strlen(poss) == 0)
                    {
                        //continue; //only key found, but no value
                        sprintf(value, "%s", "0");
                    }
                    else
                        strncpy(value, poss, strlen(poss));
                    m_currentSection[key] = value;
                }
            }
        }
        SelectSection(m_currentSectionName.c_str());
        return true;
    }

    bool Open(const char* filename)
    {
        const int bufSize = 256;
        ifstream fin;
        fin.open(filename, ios::in);
        m_currentFilename = filename;

        char cline[bufSize];
        memset(cline, 0, bufSize);
        char *poss = 0;
        char *pose = 0;

        char key[bufSize/2];
        char value[bufSize/2];

        bool sectionDetected = false;

        while(!fin.eof())
        {
            if(!sectionDetected)
            {
                memset(cline, 0, bufSize);
                fin.getline(cline, bufSize-1);
                sectionDetected = false;
            }
            poss = strstr(cline, "[");
            pose = strstr(cline, "]");
            if( poss != NULL && pose != NULL) //section detected
            {
                sectionDetected = false;
                char secName[bufSize];
                memset(secName, 0, bufSize);
                strncpy(secName, poss+1, pose-poss-1);
                SelectSection(secName);
                while(!fin.eof())
                {
                    memset(cline, 0, bufSize);
                    memset(key, 0, bufSize/2);
                    memset(value, 0, bufSize/2);
                    fin.getline(cline, bufSize-1);
                    if( strlen(cline) == 0)
                        continue; //skip empty lines

                    if( strstr(cline, "[") != NULL )
                    {
                        sectionDetected = true;
                        break; // next section detected
                    }

                    poss = cline;
                    pose = strstr(cline, "=");
                    if(pose == NULL)
                        continue; //no value pair found

                    //copy key value
                    memset(key, 0, bufSize/2);
                    strncpy(key, poss, pose-poss);

                    poss = pose+1;
                    if(strlen(poss) == 0)
                        continue; //only key found, but no value

                    strncpy(value, poss, strlen(poss));
                    m_currentSection[key] = value;
                }
            }
        }
        SelectSection(m_currentSectionName.c_str());
        fin.close();
        return true;
    }

    bool Save(const char* filename = "")
    {
        if(m_currentSection.size() > 0)
        {
            sections[m_currentSectionName] = m_currentSection;
        }
        ofstream fout;
        if( strlen(filename) > 0)
            fout.open(filename, ios::out);
        else
            fout.open(m_currentFilename.c_str(), ios::out);

        map<string , map<string, string> >::iterator iterSections;
        for(iterSections = sections.begin(); iterSections != sections.end(); ++iterSections)
        {
            fout << "[" << iterSections->first << "]" << endl;
            map<string , string >::iterator iterPairs;
            for(iterPairs = iterSections->second.begin(); iterPairs != iterSections->second.end(); ++iterPairs)
            {
                fout << iterPairs->first << "=" << iterPairs->second << endl;
            }
        }
        fout.close();
        return true;
    }

    bool SelectSection(const char* secName)
    {
        //if(m_currentSection.size() > 0)
        if(m_currentSectionName.length() > 0)
        {
            sections[m_currentSectionName] = m_currentSection;
        }
        m_currentSectionName = secName;
        m_currentSection.clear();
        if(SectionExist(secName))
            m_currentSection = sections[secName];
        else
        {
            return false;
        }
        return true;
    }

    bool SectionExist(const char* secName)
    {
        return ( sections.find(secName) != sections.end());
    }

    template <typename dataType>
    dataType Get(const char* variable, const dataType &defValue)
    {
        string retVal = "";
        try
        {
            retVal = m_currentSection.at(variable);
        }
        catch(const std::out_of_range &oor)
        {
            return defValue;
        }
        catch(...)
        {
            return defValue;
        }
        stringstream ss;
        ss.str(retVal);
        dataType valOut = defValue;
        ss >> valOut;
        return valOut;
    }


    string Get(const char* variable, const char* defValue)
    {
        string retVal = "";
        try
        {
            retVal = m_currentSection.at(variable);
        }
        catch(const std::out_of_range &oor)
        {
            return defValue;
        }
        catch(...)
        {
            return defValue;
        }
        return retVal;
    }

    string Get(const char* variable, const string &defValue)
    {
        string retVal = "";
        try
        {
            retVal = m_currentSection.at(variable);
        }
        catch(const std::out_of_range &oor)
        {
            return defValue;
        }
        catch(...)
        {
            return defValue;
        }
        return retVal;
    }

    map<string, string> GetCurrentSection()
    {
        return m_currentSection;
    }

    void Set(const char* variable, const string &value);
    template <typename dataType>
    void Set(const char* variable, const dataType &value)
    {
        stringstream ss;
        ss << value;
        m_currentSection[variable] = ss.str();
    }

    void Set(const char* variable, const char *value)
    {
        stringstream ss;
        ss.str(value);
        m_currentSection[variable] = ss.str();
    }

    void ClearSection()
    {
        m_currentSection.clear();
        sections[m_currentSectionName].clear();
    }

    void ClearAll()
    {
        m_currentSection.clear();
        sections.clear();
    }

    void Print()
    {
        map<string, map<string, string> >::iterator iter_sections;
        map<string, string>::iterator current_section;
        for(iter_sections = sections.begin(); iter_sections!=sections.end(); ++iter_sections)
        {
            cout << "[" << iter_sections->first << "]" << endl;
            for(current_section = iter_sections->second.begin(); current_section!=iter_sections->second.end(); ++current_section)
            {
                cout << current_section->first<< "=" << current_section->second << endl;
            }
        }
    }

protected:
    string m_currentFilename;
    string m_currentSectionName;
    map<string, string> m_currentSection;
    map<string, map<string, string> > sections;
};
}
#endif


