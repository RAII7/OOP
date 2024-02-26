#pragma once

class General {
private:
	unsigned int m_ID;

public:
	unsigned int ID() {
		return m_ID;
	}

	void setID(unsigned int m_ID) {
		this->m_ID = m_ID;
	}
};

