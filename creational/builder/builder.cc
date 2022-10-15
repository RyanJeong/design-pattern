/*
  Copyright 2022 Munseong Jeong <ryan.m.jeong@hotmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <string>
#include <iostream>
#include <memory>

// "Product"
class Pizza {
 public:
  Pizza() = default;
  Pizza(const Pizza& pizza) = delete;
  ~Pizza() = default;

  void SetDough(const std::string& dough) { _dough = dough; }
  void SetSauce(const std::string& sauce) { _sauce = sauce; }
  void SetTopping(const std::string& topping) { _topping = topping; }
  void Open() const {
    std::cout << "Pizza with " << _dough
        << " dough, " << _sauce
        << " sauce and " << _topping << " topping." << std::endl;
  }
 private:
  std::string _dough;
  std::string _sauce;
  std::string _topping;
};

// "Abstract Builder"
class PizzaBuilder {
 public:
  PizzaBuilder() = default;
  PizzaBuilder(const PizzaBuilder& pizza_builder) = delete;
  virtual ~PizzaBuilder() {}

  Pizza* GetPizza() { return _pizza.get(); }
  void CreateNewPizzaProduct() { _pizza = std::make_unique<Pizza>(); }
  virtual void BuildDough() = 0;
  virtual void BuildSauce() = 0;
  virtual void BuildTopping() = 0;
 protected:
  std::unique_ptr<Pizza> _pizza;
};

//----------------------------------------------------------------

class HawaiianPizzaBuilder : public PizzaBuilder {
 public:
  virtual ~HawaiianPizzaBuilder() {}

  virtual void BuildDough() { _pizza->SetDough("cross"); }
  virtual void BuildSauce() { _pizza->SetSauce("mild"); }
  virtual void BuildTopping() { _pizza->SetTopping("ham+pineapple"); }
};

class SpicyPizzaBuilder : public PizzaBuilder {
 public:
  virtual ~SpicyPizzaBuilder() {}

  virtual void BuildDough() { _pizza->SetDough("pan baked"); }
  virtual void BuildSauce() { _pizza->SetSauce("hot"); }
  virtual void BuildTopping() { _pizza->SetTopping("pepperoni+salami"); }
};

//----------------------------------------------------------------

class Cook {
 public:
  void OpenPizza() { _pizza_builder->GetPizza()->Open(); }
  void MakePizza(PizzaBuilder* pb) {
    _pizza_builder = pb;
    _pizza_builder->CreateNewPizzaProduct();
    _pizza_builder->BuildDough();
    _pizza_builder->BuildSauce();
    _pizza_builder->BuildTopping();
  }
 private:
  PizzaBuilder* _pizza_builder;
};

int main() {
  Cook cook;

  HawaiianPizzaBuilder hawaiianPizzaBuilder;
  cook.MakePizza(&hawaiianPizzaBuilder);
  cook.OpenPizza();

  SpicyPizzaBuilder spicyPizzaBuilder;
  cook.MakePizza(&spicyPizzaBuilder);
  cook.OpenPizza();

  return 0;
}
