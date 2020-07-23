#pragma once
#include <string>

class Invoice
{
public:
	Invoice( const std::string& vendor, const std::string& rfc, const std::string& date,
		const std::string& invoiceNo, const std::string& concept, const std::string& account,
		double amount, double retain, int taxRate = defTaxRate );

public:
	double GetAmount() const { return amount; }
	double GetRetain() const { return retain; }
	int GetTaxRate() const { return taxRate; }

private:
	std::string vendor;
	std::string rfc;
	std::string date;
	std::string invoiceNo;
	std::string concept;
	std::string account;
	double amount;
	double retain;
	int taxRate;
	static constexpr int defTaxRate = 16;
};