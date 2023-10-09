"""Charger sensor platform."""
from homeassistant.helpers.entity import Entity

async def async_setup_platform(hass, config, async_add_entities, discovery_info=None):
    async_add_entities([ChargerSensor()])

class ChargerSensor(Entity):
    def __init__(self):
        self._state = None

    @property
    def name(self):
        return "Charger Status"

    @property
    def state(self):
        return self._state

    async def async_update(self):
        # Implement logic to fetch charger status from your API
        # Example: status = charger.get_status()
        status = "Unknown"
        self._state = status
