/* 
 * File:   AGpio.h
 * Author: barth
 *
 * Created on 30 novembre 2014, 23:09
 */

#ifndef AGPIO_H
#define	AGPIO_H

class AGpio {
public:
    AGpio();
    AGpio(const AGpio& orig);
    virtual ~AGpio();
     
    virtual void init(int pin_num) = 0;
    virtual bool read(int pin_num) const = 0;
    virtual void write(int pin_num, bool value) = 0;
    virtual void reset() = 0;
    
private:

};

#endif	/* AGPIO_H */

