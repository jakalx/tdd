#include "person_service_impl.h"
#include "personen_service_exception.h"
#include "repository_exception.h"

person_service_impl::person_service_impl(person_repository &repo, person_validator v)
  : repo(repo), validator(v)
{
}

void person_service_impl::speichern(person &p)
{
  if (const auto validation_error = validator (p); validation_error) {
    throw personen_service_exception(validation_error->c_str());
  }

  try {
    repo.save(p);
  } catch (const repository_exception &ex) {
    const auto msg = "repository exception in underlying layer: " + std::string(ex.what());
    throw personen_service_exception(msg.c_str());
  } catch (const std::exception &ex) {
    const auto msg = "exception in underlying layer: " + std::string(ex.what());
    throw personen_service_exception(msg.c_str());
  } catch (...) {
    throw personen_service_exception("unknown exception in underlying layer");
  }
}


std::optional<person> person_service_impl::findePersonMitId(std::string id)
{
	try {
		return  repo.find_by_id(id);
	} catch (const repository_exception &ex)
	{
		return std::nullopt;
	}
}
