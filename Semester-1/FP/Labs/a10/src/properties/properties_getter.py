from jproperties import Properties


def run():
    settings = Properties()
    with open('settings.properties', 'rb') as settings_file:
        settings.load(settings_file)
    return settings.get("repository").data, settings.get("students").data, settings.get("disciplines").data, \
                            settings.get("grades").data


if __name__ == '__main__':
    print(run())
