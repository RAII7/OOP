#pragma once

#include <string>
#include "General.h"

class Customer : public General {
private:
	unsigned int m_number;
	std::string m_contactFace;
	std::string m_address;

public:
	unsigned int number() {
		return m_number;
	}
	std::string contactFace() {
		return m_contactFace;
	}
	std::string address() {
		return m_address;
	}

	void setNumber(unsigned int m_number) {
		this->m_number = m_number;
	}
	void setContactFace(std::string m_contactFace) {
		this->m_contactFace = m_contactFace;
	}
	void setAddress(std::string m_address) {
		this->m_address = m_address;
	}
};
