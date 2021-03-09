// Quinton Negron
// Few comments describing the class Points2

#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

namespace teaching_project {

template<typename Object>
class Points2{
    public:
        Points2() //defualt constructor
        {
            size_ = 0;
            sequence_ = nullptr;
        }
        
        Points2(const Points2 &rhs)// Copy-constructor.
        {
            sequence_ = new std::array<Object, 2>[rhs.size_]; //Create 2d array of same size
            size_=rhs.size_; //Note the new size
            for (int i=0;i<size_;i++) { 
                for (int j=0;j<2;j++) {
                    sequence_[i][j]=rhs.sequence_[i][j]; //copy every value
                }
            }
        }
        
        Points2(Points2 && rhs)  // Move Constructor
        {
            sequence_=std::move(rhs.sequence_); 
            size_=std::move(rhs.size_);
            rhs.sequence_ = nullptr;
            rhs.size_=0;
        }
        
        Points2 & operator= (const Points2 &rhs) //copy assignment
        {
            if (size_>1) {delete[] sequence_;} //get rid of anything old
            else if (size_==1) {delete sequence_;}  //get rid of anything old
            sequence_ = new std::array<Object, 2>[rhs.size_]; 
            size_=rhs.size_;
            for (int i=0;i<size_;i++) {
                for (int j=0;j<2;j++) {
                    sequence_[i][j]=rhs.sequence_[i][j];
                }
            }
            return *this;
        }
        
        Points2 & operator= (Points2 && rhs) //Move assignment
        {
            if (size_>1) {delete[] sequence_;}
            else if (size_==1) {delete sequence_;}
            sequence_=std::move(rhs.sequence_);
            size_=std::move(rhs.size_);
            rhs.sequence_ = nullptr;
            rhs.size_=0;
            return *this;
        }
        
        ~Points2() //destructor
        {
            if (size_>1) {delete[] sequence_;}
            else if (size_==1) {delete sequence_;}
            sequence_=nullptr;
        }
        //End of Big five
        
        Points2(const std::array<Object, 2>& item) // One parameter constructor.
        {
            size_ = 1;
            sequence_ = new std::array <Object, 2>;
            sequence_[0][0]=item[0];
            sequence_[0][1]=item[1];
        }
        
        // Read a chain from standard input.
        void ReadPoints2()
        {
            int i=0,j=0;
            if (size_>1) {delete[] sequence_;}
            else if (size_==1) {delete sequence_;}
            size_=0;

            std::string input_line;
            std::getline(std::cin, input_line);
            if (input_line.empty())
            {
                return;
            }


            
            std::stringstream input_stream(input_line);
            if (input_line.find("(")!=std::string::npos) {
                for (char c: input_line) {
                    if (c==')') size_++;
                }
                //int count=0;
                //std::string nonsense;
                //while (input_count>>nonsense) count++;
                //size_=count;     
                
                
                sequence_=new std::array<Object,2>[size_];
                
                std::string pair;
                
                while (input_stream >> pair) {
                    while (pair[pair.size()-1]!=')') {
                        std::string temp;
                        input_stream >> temp;
                        pair+=temp;
                    }
                    if (input_line.find(".")!=std::string::npos) {
                        int poscomma=pair.find(",");
                        int posleft=pair.find("(");
                        int posright=pair.find(")");

                        std::string first=pair.substr(posleft+1,poscomma-1);
                        std::string second=pair.substr(poscomma+1,posright-poscomma-1);

                        double firstdouble= std::atof(first.c_str());
                        double seconddouble= std::atof(second.c_str());

                        sequence_[i][0]=firstdouble;
                        sequence_[i][1]=seconddouble;
                        
                    i++;
                    }

                    else {
                        int poscomma=pair.find(",");
                        int posleft=pair.find("(");
                        int posright=pair.find(")");
                        std::string first=pair.substr(posleft+1,poscomma-1);
                        std::string second=pair.substr(poscomma+1,posright-poscomma-1);

                        int firstint= std::atoi(first.c_str());
                        int secondint= std::atoi(second.c_str());
            
                        sequence_[i][0]=firstint;
                        sequence_[i][1]=secondint;
                        

                    i++;

                    }
                }
            }
            else {
                std::string s;
                input_stream>>s;
                size_=std::atoi(s.c_str());
                sequence_=new std::array<Object,2>[size_];
                bool doub=false;
                if (input_line.find(".")!=std::string::npos) {doub=true;}
                while (input_stream>>s) {
                    if (doub==true) sequence_[i][j]=std::atof(s.c_str());
                    else sequence_[i][j]=std::atoi(s.c_str());
                    if (j==1) i++;
                    j=(j+1)%2;
                }
            }
        


        return;
        }
        
        size_t size() const
        {
            return size_;
        }
        
        const std::array<Object, 2>& operator[](size_t location) const
        {
            if ((location >= 0) && (location < size_))
            {
                return sequence_[location];
            }
            else
            {
                abort();
            }
        }
        
        //  @return their sum. If the sequences are not of the same size, append the
        //    result with the remaining part of the larger sequence.
        friend Points2 operator+(const Points2 &c1, const Points2 &c2)
        {
            Points2 point;
            if (c1.size_<c2.size_) {
                point=c2;
                for (int i=0;i<c1.size_;i++) { 
                    for (int j=0;j<2;j++) {
                        point.sequence_[i][j]=c1.sequence_[i][j]+c2.sequence_[i][j]; //sum every value
                    }
                }
            }
            
            else {
                point=c1;
                for (int i=0;i<c2.size_;i++) { 
                    for (int j=0;j<2;j++) {
                        point.sequence_[i][j]=c1.sequence_[i][j]+c2.sequence_[i][j]; //sum every value
                    }
                }
            }


            return point;

            
        }
        friend std::ostream &operator<<(std::ostream &out, const Points2 &some_points2)
        {
            for (int i=0;i<some_points2.size_;i++) { 
                out<<"(";
                for (int j=0;j<2;j++) {
                    out<<some_points2.sequence_[i][j];
                    if (j==0) out<<",";//<<std::endl; //copy every value
                }
                out<<") ";
            }
            return out;
        }

        // void print() { //you can kill this
        //     for (int i=0;i<size_;i++) { 
        //         std::cout<<"(";
        //         for (int j=0;j<2;j++) {
        //             std::cout<<sequence_[i][j];
        //             if (j==0) std::cout<<",";//<<std::endl; //copy every value
        //         }
        //         std::cout<<") ";
        //     }
        // }

    private:
        std::array<Object, 2>* sequence_; // Sequence of points.
        size_t size_; // Size of sequence.
        };
}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
