#pragma once

#include <iostream>
#include "pugixml.hpp"
#include "Registry.h"

struct Registries {
private:
	Registry<Product> reg_products;
	Registry<Customer> reg_customers;
	Registry<Deal> reg_deals;
public:
	Registry<Product>& products() {
		return reg_products;
	}

	Registry<Customer>& customers() {
		return reg_customers;
	}

	Registry<Deal>& deals() {
		return reg_deals;
	}

};

class Data {
protected:
	Registries reg_all;

public:
	Registries& registries() {
		return reg_all;
	}

	void setRegistries(Registries& reg_all) {
		this->reg_all = reg_all;
	}

	virtual bool read(const std::string& oldFileName) = 0 {}
	virtual bool write(const std::string& newFileName) = 0 {}
};

class DataXML : public Data {
public:

	bool read(const std::string& FileName) override
	{
		pugi::xml_document doc;
		if (!doc.load_file(FileName.c_str())) {
			std::cout << "Load file failed.\n";
			return false;
		}

		pugi::xml_node root = doc.child("ordermanagment");

		pugi::xml_node node_products = root.child("products");
		for (pugi::xml_node node_product = node_products.first_child(); node_product; node_product = node_product.next_sibling()) {
			Product product;

			product.setID(node_product.attribute("ID").as_uint());
			product.setName(node_product.attribute("name").as_string());
			product.setRozPrice(node_product.attribute("rozPrice").as_double());
			product.setOptPrice(node_product.attribute("optPrice").as_double());
			product.setDescription(node_product.attribute("description").as_string());

			reg_all.products().regist(product);
		}

		pugi::xml_node node_customers = root.child("customers");
		for (auto node_customer : node_customers.children()) {
			Customer customer;

			customer.setID(node_customer.attribute("ID").as_uint());
			customer.setNumber(node_customer.attribute("number").as_uint());
			customer.setContactFace(node_customer.attribute("contactFace").as_string());
			customer.setAddress(node_customer.attribute("address").as_string());

			reg_all.customers().regist(customer);
		}

		pugi::xml_node node_deals = root.child("deals");
		for (auto node_deal : node_deals.children()) {
			Deal deal;

			deal.setID(node_deal.attribute("ID").as_uint());
			deal.setDate(node_deal.attribute("date").as_string());
			deal.setAmount(node_deal.attribute("amount").as_uint());
			deal.setDate(node_deal.attribute("type").as_string());

			pugi::xml_node node_productsID = node_deal.child("products_id");
			std::vector<unsigned int> productsID;
			for (auto node_productID : node_productsID.children()) {
				unsigned int productID = node_productID.attribute("ID").as_uint();
				productsID.push_back(productID);
			}
			deal.setProductsID(productsID);

			reg_all.deals().regist(deal);
		}

		return true;
	}

	bool write(const std::string& FileName) override
	{
		pugi::xml_document doc;

		pugi::xml_node declaration_node = doc.append_child(pugi::node_declaration);
		declaration_node.append_attribute("version") = "1.0";
		declaration_node.append_attribute("encoding") = "UTF-8";

		pugi::xml_node root = doc.append_child("dealmanagment");

		pugi::xml_node node_products = root.append_child("products");
		for (auto iter = reg_all.products().begin(); iter != reg_all.products().end(); iter++) {
			pugi::xml_node node_product = node_products.append_child("product");
			Product product = reg_all.products().getById(*iter);

			node_product.append_attribute("ID").set_value(product.ID());
			node_product.append_attribute("name").set_value(product.name().c_str());
			node_product.append_attribute("rozPrice").set_value(product.rozPrice());
			node_product.append_attribute("optPrice").set_value(product.optPrice());
			node_product.append_attribute("description").set_value(product.description().c_str());
		}

		pugi::xml_node node_customers = root.append_child("customers");
		for (auto iter = reg_all.customers().begin(); iter != reg_all.customers().end(); iter++) {
			pugi::xml_node node_customer = node_customers.append_child("customer");
			Customer customer = reg_all.customers().getById(*iter);

			node_customer.append_attribute("ID").set_value(customer.ID());
			node_customer.append_attribute("number").set_value(customer.number());
			node_customer.append_attribute("contactFace").set_value(customer.contactFace().c_str());
			node_customer.append_attribute("address").set_value(customer.address().c_str());
		}

		pugi::xml_node node_deals = root.append_child("deals");
		for (auto iter = reg_all.deals().begin(); iter != reg_all.deals().end(); iter++) {
			pugi::xml_node node_deal = node_deals.append_child("deal");
			Deal deal = reg_all.deals().getById(*iter);

			node_deal.append_attribute("ID").set_value(deal.ID());
			node_deal.append_attribute("date").set_value(deal.date().c_str());
			node_deal.append_attribute("amount").set_value(deal.amount());
			node_deal.append_attribute("type").set_value(deal.type().c_str());

			pugi::xml_node node_productsID = node_deal.append_child("products_id");
			std::vector<unsigned int> productsID = deal.productsID();
			for (auto iter = productsID.begin(); iter != productsID.end(); ++iter) {
				pugi::xml_node node_productID = node_productsID.append_child("product_id");
				node_productID.append_attribute("ID").set_value(*iter);
			}
		}

		if (!doc.save_file(FileName.c_str())) {
			std::cout << "Save file failed.\n";
			return false;
		}

		return true;
	}
};
