//
//  list.cpp
//  homework4_q3
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;
// abstract class
class MenuItem
{
public:
    MenuItem(string nm) : m_name(nm) {}
    virtual ~MenuItem() {}
    string name() const { return m_name; }
    virtual bool add(MenuItem* m) = 0;
    virtual const vector<MenuItem*>* menuItems() const = 0;
private:
    string m_name;
};

class PlainMenuItem : public MenuItem   // PlainMenuItem allows no submenus
{
public:
    PlainMenuItem(string nm) : MenuItem(nm) {}
    virtual bool add(MenuItem* m) { return false; }
    virtual const vector<MenuItem*>* menuItems() const { return NULL; }
};

class CompoundMenuItem : public MenuItem  // CompoundMenuItem allows submenus
{
public:
    CompoundMenuItem(string nm) : MenuItem(nm) {}
    virtual ~CompoundMenuItem();
    virtual bool add(MenuItem* m) { m_menuItems.push_back(m); return true; }
    virtual const vector<MenuItem*>* menuItems() const { return &m_menuItems; }
private:
    vector<MenuItem*> m_menuItems;
};

CompoundMenuItem::~CompoundMenuItem()
{
    for (int k = 0; k < m_menuItems.size(); k++)
        delete m_menuItems[k];
}

void listAll(const MenuItem* m, string path) // two-parameter overload
{
//    You will write this code.
    //cout << "Call Trace: " << path << endl;
    string temp = path;
    if (path != "") // if you're not starting from scratch or just being directed over from the one-parameter version
    {
        cout << path << endl;
        temp = path + "/";
        
    }
    if (m->menuItems()->empty()) { // this'll get called when you've run a complete path
        cout << path << endl; }
    else
    {
        const vector<MenuItem*>* miv = m->menuItems();
//        cout << "SIZE" << miv->size() << endl;
        for (size_t n = 0; n != miv->size(); n++) // what is size_t
        {
            // this is the problem part
//            cout << "IDX" << n << endl;
            if ((*miv)[n]->menuItems() != NULL && !(*miv)[n]->menuItems()->empty())
            {// if it has subdomains, go explore those first.
//                cout << "NOT EMPTY" << endl;
                listAll((*miv)[n], temp + (*miv)[n]->name());

            } else {
//                cout << "EMPTY" << endl;
                cout << temp + (*miv)[n]->name() << endl; // if there are no further subdomains, start printing.
            }
        }
    }
}

void listAll(const MenuItem* m)  // one-parameter overload
{
    if (m != NULL)
        listAll(m, "");
}

int main()
{
    CompoundMenuItem* cm0 = new CompoundMenuItem("New");
    cm0->add(new PlainMenuItem("Window"));
    CompoundMenuItem* cm1 = new CompoundMenuItem("File");
    cm1->add(cm0);
    cm1->add(new PlainMenuItem("Open"));
    cm1->add(new PlainMenuItem("Exit"));
    CompoundMenuItem* cm2 = new CompoundMenuItem("Help");
    cm2->add(new PlainMenuItem("Index"));
    cm2->add(new PlainMenuItem("About"));
    CompoundMenuItem* cm3 = new CompoundMenuItem("");  // main menu bar
    cm3->add(cm1);
    cm3->add(new PlainMenuItem("Refresh"));  // no submenu
    cm3->add(new CompoundMenuItem("Under Development")); // no submenus yet
    cm3->add(cm2);
    listAll(cm3);
    delete cm3;
}