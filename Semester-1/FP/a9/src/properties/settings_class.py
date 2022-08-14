from jproperties import Properties


class Settings:
    def __init__(self, file_name):
        self._file_name = file_name
        self._settings = Properties()
        self.run()
        self.repository = self._settings.get("repository").data
        self.students = self._settings.get("students").data
        self.disciplines = self._settings.get("disciplines").data
        self.grades = self._settings.get("grades").data

    def run(self):
        with open(self._file_name, 'rb') as settings_file:
            self._settings.load(settings_file)
