
#ifndef IGPIO_H
#define	IGPIO_H

class IGpio {
public:
    virtual ~IGpio() {}
     
    virtual void init(int pin_num) = 0;
    virtual bool read(int pin_num) const = 0;
    virtual void write(int pin_num, bool value) = 0;
    virtual void reset() = 0;
    
private:

};

#endif	/* IGPIO_H */

