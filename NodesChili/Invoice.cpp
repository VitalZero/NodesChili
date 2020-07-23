#include "Invoice.h"

Invoice::Invoice( const std::string & vendor, const std::string & rfc, const std::string & date, 
	const std::string & invoiceNo, const std::string & concept, const std::string & account, 
	double amount, double retain, int taxRate )
	:
	vendor(vendor), rfc(rfc), date(date), invoiceNo(invoiceNo), concept(concept),
	account(account), amount(amount), retain(retain), taxRate(taxRate)
{}
