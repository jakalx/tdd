#include <gmock/gmock.h>

#include "PersonRepository.h"

class Mockperson_repository : public person_repository {
 public:
  MOCK_METHOD(void, save, (person p), (override));
  MOCK_METHOD(void, update, (person p), (override));
  MOCK_METHOD(void, remove, (person p), (override));
  MOCK_METHOD(std::vector<person>, find_all, (), (const, override));
  MOCK_METHOD(person, find_by_id, (std::string id), (const, override));
};
