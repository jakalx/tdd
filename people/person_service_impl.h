#pragma once

#include <string>
#include "PersonRepository.h"
#include "Person.h"
#include <optional>
#include <functional>

using person_validator = std::function<std::optional<std::string> (const person &)>;

class person_service_impl
{
	person_repository &repo;
  person_validator validator;

public:
  person_service_impl(person_repository &repo, person_validator validator);

        /*
	 * 1. vorname min 2 Zeichen (evtl. nullprüfung) -> person_service_exception
	 * 2. nachname soll min 2 Zeichen (evtl. nullprüfung) -> person_service_exception
	 *
	 * 3. vorname darf nicht Attila sein -> person_service_exception
	 *
	 * 4. Exception im darunter liegenden Layer -> -> person_service_exception
	 * 
	 */
	void speichern(person &p) ;
  void speichern(std::string vorname, std::string nachname) {
    person p;
    p.SetVorname(vorname);
    p.SetNachname(nachname);
    speichern (p);
  }


        /*
	 * Kein Treffer -> RepoException => Leeres Optional
	 * Treffer -> Befülltes Optional
	 * 
	 */
	std::optional<person> findePersonMitId(std::string id);
};

