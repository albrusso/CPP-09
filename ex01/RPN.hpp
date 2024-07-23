/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:00:20 by albrusso          #+#    #+#             */
/*   Updated: 2024/07/23 18:46:47 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <istream>
# include <sstream>
# include <stack>
# include <cstdlib>


class RPN
{
	private:
		std::string _exp;
		std::stack <int> _s;
	public:
		RPN(void);
		RPN(std::string exp);
		RPN(const RPN &copy);
		RPN &operator=(const RPN &r);
		~RPN(void);

		int isNumber(std::string tok);
		int isOperator(std::string tok);
		int executeOperation(std::string operation, int a, int b);
		int validate(void);
		int execute(void);
};

#endif