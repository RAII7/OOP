#pragma once

#include <string>
#include <vector>
#include "General.h"

class Deal : public General {
private:
	std::string m_date;
	std::vector<unsigned int> m_productsID;
	unsigned int m_amount;
	unsigned int m_customerID;
	std::string m_type;

public:
	std::string date() {
		return m_date;
	}
	std::vector<unsigned int>& productsID() {
		return m_productsID;
	}
	unsigned int amount() {
		return m_amount;
	}
	unsigned int customerID() {
		return m_customerID;
	}
	std::string type() {
		return m_type;
	}

	void setDate(std::string date) {
		this->m_date = std::move(date);
	}
	void setProductsID(std::vector<unsigned int>& productsID) {
		this->m_productsID = std::move(productsID);
	}
	void setAmount(unsigned int amount) {
		this->m_amount = std::move(amount);
	}
	void setCustomerID(unsigned int customerID) {
		this->m_amount = std::move(customerID);
	}
	void setType(std::string type) {
		this->m_type = std::move(type);
	}
};
