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

// an implementation for using std::unique_ptr on c++11
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// "Product"
class Pizza {
 public:
  Pizza() = default;
  Pizza(const Pizza&) = delete;
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
  PizzaBuilder(const PizzaBuilder&) = delete;
  virtual ~PizzaBuilder() {}

  Pizza* GetPizza() { return _pizza.get(); }
  void CreateNewPizzaProduct() { _pizza = make_unique<Pizza>(); }
  virtual void BuildDough() = 0;
  virtual void BuildSauce() = 0;
  virtual void BuildTopping() = 0;
 protected:
  std::unique_ptr<Pizza> _pizza;
};

//----------------------------------------------------------------

class HawaiianPizzaBuilder : public PizzaBuilder {
 public:
  HawaiianPizzaBuilder() = default;
  HawaiianPizzaBuilder(const HawaiianPizzaBuilder&) = delete;
  ~HawaiianPizzaBuilder() final {}

  void BuildDough() final { _pizza->SetDough("cross"); }
  void BuildSauce() final { _pizza->SetSauce("mild"); }
  void BuildTopping() final { _pizza->SetTopping("ham+pineapple"); }
};

class SpicyPizzaBuilder : public PizzaBuilder {
 public:
  SpicyPizzaBuilder() = default;
  SpicyPizzaBuilder(const SpicyPizzaBuilder&) = delete;
  ~SpicyPizzaBuilder() final {}

  void BuildDough() final { _pizza->SetDough("pan baked"); }
  void BuildSauce() final { _pizza->SetSauce("hot"); }
  void BuildTopping() final { _pizza->SetTopping("pepperoni+salami"); }
};

//----------------------------------------------------------------

class Cook {
 public:
  void MakePizza(PizzaBuilder* pb) {
    _pizza_builder = pb;
    _pizza_builder->CreateNewPizzaProduct();
    _pizza_builder->BuildDough();
    _pizza_builder->BuildSauce();
    _pizza_builder->BuildTopping();
  }
  void OpenPizza() { _pizza_builder->GetPizza()->Open(); }
 private:
  PizzaBuilder* _pizza_builder;
};

int main() {
  Cook cook;

  HawaiianPizzaBuilder hawaiian_pizza_builder;
  cook.MakePizza(&hawaiian_pizza_builder);
  cook.OpenPizza();

  SpicyPizzaBuilder spicy_pizza_builder;
  cook.MakePizza(&spicy_pizza_builder);
  cook.OpenPizza();

  return 0;
}
