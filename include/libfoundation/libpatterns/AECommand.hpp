/*
 * AECommand.hpp
 *
 *  Created on: Apr 28, 2014
 *      Author: ross
 */

#ifndef AECOMMAND_HPP_
#define AECOMMAND_HPP_

class AECommand {

public:

	AECommand();
	virtual ~AECommand() {}
	virtual void execute() = 0;
};



#endif /* AECOMMAND_HPP_ */
