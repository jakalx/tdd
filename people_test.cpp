#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "people/PersonRepositoryMock.h"
#include "people/person_service_impl.h"
#include "people/personen_service_exception.h"
#include "people/repository_exception.h"

using std::basic_string;
using std::optional;

using namespace ::testing;

std::optional<std::string> validate_forename(const person& p) {
  if (p.GetVorname().size() < 2)
    return "invalid vorname: less than two chars";
  else
    return {};
}
std::optional<std::string> validate_surname(const person &p)
{
  if (p.GetNachname().size() < 2)
    return "invalid nachname: less than two chars";
  else
    return {};
}

optional<std::string> concat(optional<std::string> a, optional<std::string> b)
{
  if (a) {
    if (b) {
      return *a + ", " + *b;
    } else {
      return *a;
    }
  } else {
    if (b) {
      return *b;
    } else {
      return {};
    }
  }
}

auto concat(person_validator f, person_validator g) {
  return [=] (const person& p) {
    return concat (f(p), g(p));
  };
}

class Mockperson_validator
{
public:
  MOCK_METHOD(std::optional<std::string>, validate, (const person &), (const));

  std::optional<std::string> operator()(const person &p) const
  {
    return validate(p);
  }
};

class person_service_impl_Test : public ::testing::Test
{
protected:
  person make_person(std::string forename, std::string surname, std::string id = "")
  {
    person p;
    p.SetVorname(forename);
    p.SetNachname(surname);
    p.SetId(id);
    return p;
  }

  Mockperson_repository person_repository_Mock;
  NiceMock<Mockperson_validator> person_validator_Mock;
  person_service_impl testee{ person_repository_Mock, std::ref(person_validator_Mock) };
  person valid_person{ [this] { return make_person ("john", "doe");}()};
};

#define EXPECT_THROW_WHAT(code, exc, text)                  \
  do {                                                      \
    try {                                                   \
      (code);                                               \
      FAIL() << "no exception thrown!";                     \
    } catch (const exc& e) {                                \
      EXPECT_THAT(e.what(), ::testing::StrEq (text));       \
    } catch (...)  {                                        \
      FAIL() << "other exception thrown. expected ";        \
    }                                                       \
  }                                                         \
  while (0)

TEST_F(person_service_impl_Test, speichern__vorname_less_than_two_chars_then_a_personen_service_exception_is_thrown)
{
  EXPECT_CALL(person_validator_Mock, validate(_)).WillOnce(Invoke(concat(validate_forename, validate_surname)));
  EXPECT_THROW_WHAT(testee.speichern(make_person("j", "doe")), personen_service_exception, "invalid vorname: less than two chars");
}

TEST_F(person_service_impl_Test, speichern__nachname_less_than_two_chars_then_a_personen_service_exception_is_thrown) {
  EXPECT_CALL(person_validator_Mock, validate(_)).WillOnce(Invoke(concat(validate_forename, validate_surname)));
  EXPECT_THROW_WHAT(testee.speichern(make_person("john", "d")), personen_service_exception, "invalid nachname: less than two chars");
}

TEST_F(person_service_impl_Test, speichern__vorname_must_not_be_Attila__personen_service_exception_is_thrown)
{
  EXPECT_CALL(person_validator_Mock, validate(_)).WillOnce(Return("invalid vorname: Attila"));
  EXPECT_THROW_WHAT(testee.speichern(make_person("Attila", "Hunnenkoenig")), personen_service_exception, "invalid vorname: Attila");
}

TEST_F(person_service_impl_Test, speichern__exception_in_underlying_repo__personen_service_exception_is_thrown)
{
  EXPECT_CALL(person_repository_Mock, save(_)).WillRepeatedly(Throw(std::exception ("repo down")));
  EXPECT_THROW_WHAT(testee.speichern(valid_person), personen_service_exception, "exception in underlying layer: repo down");
}

TEST_F(person_service_impl_Test, speichern__happy_day__person_is_forwarded_to_repository)
{
  {
    InSequence seq;
    EXPECT_CALL(person_validator_Mock, validate(_)).WillRepeatedly(Return(std::nullopt));
    EXPECT_CALL(person_repository_Mock, save(valid_person));
  }
  testee.speichern(valid_person);
}

TEST_F(person_service_impl_Test, speichern__happy_day__person_is_passed_with_specified_input_parameters_to_repo)
{
  person actual;
  EXPECT_CALL(person_repository_Mock, save (_)).WillOnce(SaveArg<0>(&actual));
  testee.speichern(valid_person.GetVorname(), valid_person.GetNachname());
  EXPECT_THAT(actual.GetVorname(), Eq("john"));
  EXPECT_THAT(actual.GetNachname(), Eq("doe"));
}

TEST_F(person_service_impl_Test, findePersonMitId__when_lookup_fails_with_repository_exception__nullopt_is_returned)
{
  repository_exception to_be_thrown;
  EXPECT_CALL(person_repository_Mock, find_by_id(_)).WillOnce(Throw(to_be_thrown));
  EXPECT_EQ(std::nullopt, testee.findePersonMitId("42"));
}

TEST_F(person_service_impl_Test, findePersonMitId__happy_day__repo_returns_person)
{
  const auto actual = make_person("John", "Doe", "42");
  EXPECT_CALL(person_repository_Mock, find_by_id("42")).WillOnce(Return(actual));
  EXPECT_EQ(actual, testee.findePersonMitId("42"));
}
