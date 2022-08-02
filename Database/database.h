#ifndef DATABASE_H
#define DATABASE_H

class Database
{
public:
    Database();
    bool getIsOpen() const;

private:
    void openDataBase();
private:
    bool isOpen;
};

#endif // DATABASE_H
