"""Config flow for Charger integration."""
from homeassistant import config_entries

class ChargerConfigFlow(config_entries.ConfigFlow, domain="ablsalto_charger"):
    async def async_step_user(self, user_input=None):
        return self.async_show_form(
            step_id="user", data_schema=None
        )

    async def async_step_import(self, user_input):
        return self.async_create_entry(title="Charger", data={})
