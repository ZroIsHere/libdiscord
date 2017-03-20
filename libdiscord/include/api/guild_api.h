#pragma once

#include "common.h"
#include "guild.h"

namespace discord
{
  class integration;
  class overwrite;

  namespace api
  {
    namespace guild
    {
      /** Modify the attributes of a guild.
       *
       * @param guild_id The guild to modify
       * @param guild A guild whose attributes will be sent.
       * @return The modified guild object.
       */
      pplx::task<discord::guild> modify(connection_state* conn, snowflake guild_id, discord::guild guild);

      /** Removes a guild entirely. Cannot be undone.
       *
       * @param guild_id The guild to remove.
       * @return The guild that was removed.
       */
      pplx::task<discord::guild> remove(connection_state* conn, snowflake guild_id);

      /** Get a list of channels in this guild.
       *
       * @param guild_id The guild to grab the channels from.
       * @return A list of channels in the given guild.
       */
      pplx::task<std::vector<discord::channel>> get_channels(connection_state* conn, snowflake guild_id);

      /** Create a new text channel in a guild.
       *
       * @param guild_id The guild to add a text channel to.
       * @param name The name of the new channel.
       * @param permission_overwrites An array of permission overwrites to assign to this channel.
       * @return The channel that was created.
       */
      pplx::task<discord::channel> create_text_channel(connection_state* conn, snowflake guild_id, std::string name, std::vector<overwrite> permission_overwrites = {});

      /** Create a new voice channel in a guild.
       *
       * @param guild_id The guild to add a voice channel to.
       * @param name The name of the new channel.
       * @param bitrate The bitrate for this voice channel.
       * @param user_limit The user limit for this voice channel.
       * @param permission_overwrites An array of permission overwrites to assign to this channel.
       * @return The channel that was created.
       */
      pplx::task<discord::channel> create_voice_channel(connection_state* conn, snowflake guild_id, std::string name, uint32_t bitrate = 96000, uint32_t user_limit = 99, std::vector<overwrite> permission_overwrites = {});

      /** Sets several channel positions at once.
       *
       * @param guild_id The guild that owns the channels to be positioned.
       * @param positions A mapping of channel ids to positions which will be set.
       * @return The list of channels in the guild.
       */
      pplx::task<std::vector<discord::channel>> modify_channel_positions(connection_state* conn, snowflake guild_id, const std::map<snowflake, uint32_t>& positions);

      /** Get a member of a guild.
       *
       * @param guild_id The guild to search for the member in.
       * @param user_id The user id of the member to get.
       * @return The member that was found.
       */
      pplx::task<member> get_member(connection_state* conn, snowflake guild_id, snowflake user_id);

      /** Gets a list of members in the guild.
       *
       * @param guild_id The guild to list members from.
       * @param limit The amount of members to list. Can be between 1-1000 inclusive.
       * @param after The id of the member to search after. Used for pagination.
       * @return A list of members from the guild.
       */
      pplx::task<std::vector<member>> get_members(connection_state* conn, snowflake guild_id, uint32_t limit = 1, snowflake after = 0);

      /** Adds a member to a guild. Requires an OAuth2 access token.
       *
       * @param guild_id The guild to add the user to.
       * @param user_id The user to add to the guild.
       * @param access_token The access token that gives this user guilds.join permission.
       * @param nick The nickname to give this user.
       * @param roles The roles to give this user.
       * @param muted Whether or not this user should be muted.
       * @param deafened Whether or not this user should be deaf.
       * @return Success status.
       */
      pplx::task<bool> add_member(connection_state* conn, snowflake guild_id, snowflake user_id, std::string access_token, std::string nick = "", std::vector<role> roles = {}, bool muted = false, bool deafened = false);

      /** Modify a member in the guild.
       *
       * @param guild_id The guild that has the user to be modified.
       * @param user_id The user to modify.
       * @param nick The nickname to give the user.
       * @param roles The roles to give the user.
       * @param muted Whether or not this user should be muted.
       * @param deafened Whether or not this user should be deaf.
       * @param channel_id Voice channel to move user to.
       * @return Success status.
       */
      pplx::task<bool> modify_member(connection_state* conn, snowflake guild_id, snowflake user_id, std::string nick = "", std::vector<role> roles = {}, bool muted = false, bool deafened = false, snowflake channel_id = 0);

      /** Set the current user's nickname in this guild.
       *
       * @param guild_id The guild to set the nickname in.
       * @param nick The nickname to set.
       */
      pplx::task<bool> set_nickname(connection_state* conn, snowflake guild_id, std::string nick);

      /** Add a role to a member.
       *
       * @param guild_id The guild where the member and role are.
       * @param user_id The member to add the role to.
       * @param role_id The role to add.
       * @return Success status.
       */
      pplx::task<bool> add_member_role(connection_state* conn, snowflake guild_id, snowflake user_id, snowflake role_id);

      /** Remove a role from a member.
       *
       * @param guild_id The guild where the member and role are.
       * @param user_id The member to remove the role from.
       * @param role_id The role to remove.
       */
      pplx::task<bool> remove_member_role(connection_state* conn, snowflake guild_id, snowflake user_id, snowflake role_id);

      /** Remove a member from a guild.
       *
       * @param guild_id The guild to remove the member from.
       * @param user_id The member to remove.
       */
      pplx::task<bool> remove_member(connection_state* conn, snowflake guild_id, snowflake user_id);

      /** Get a list of bans that the guild has.
       *
       * @param guild_id The guild to list bans from.
       * @return A list of bans that are currently active in the guild.
       */
      pplx::task<std::vector<discord::user>> get_bans(connection_state* conn, snowflake guild_id);

      /** Bans a member from the guild.
       *
       * @param guild_id The guild to ban the member from.
       * @param user_id The member to ban from the guild.
       * @param delete_x_days Number of days worth of messages to delete. Can be from 0-7.
       * @return Success status.
       */
      pplx::task<bool> ban(connection_state* conn, snowflake guild_id, snowflake user_id, uint32_t delete_x_days);

      /** Unbans a member from the guild.
       *
       * @param guild_id The guild to unban the member from.
       * @param user_id The member to unban.
       * @return Success status.
       */
      pplx::task<bool> unban(connection_state* conn, snowflake guild_id, snowflake user_id);

      /** Gets a list of roles that belong to the guild.
       *
       * @param guild_id The guild to get the roles from.
       * @return A list of roles that belong to the guild.
       */
      pplx::task<std::vector<role>> get_roles(connection_state* conn, snowflake guild_id);

      /** Creates a new role in a guild.
       *
       * @param guild_id The guild to add the new role to.
       * @param name The name of the new role.
       * @param permissions permissions for the new role.
       * @param rgb_color The color of the new role.
       * @param hoist Whether or not this role should be hoisted into its own group.
       * @param mentionable Whether or not this role is mentionable.
       * @return The role that was created.
       */
      pplx::task<role> create_role(connection_state* conn, snowflake guild_id, std::string name, permission permissions, uint32_t rgb_color = 0, bool hoist = false, bool mentionable = false);

      /** Modifies the raw position of a role.
       *
       * @param guild_id The guild that owns the roles.
       * @param positions A map of role ids to positions.
       * @return The list of roles from the server.
       */
      pplx::task<std::vector<role>> modify_role_positions(connection_state* conn, snowflake guild_id, const std::map<snowflake, uint32_t>& positions);

      /** Modify the attributes of a role.
       *
       * @param guild_id The guild that owns this role.
       * @param role_id The id of the role to modify.
       * @param name The new name of the role.
       * @param permissions The new permissions for this role.
       * @param rgb_color The new color for this role.
       * @param hoist The new hoist value for this role.
       * @param mentionable The new mentionable value for this role.
       * @return The role that was updated.
       */
      pplx::task<role> modify_role(connection_state* conn, snowflake guild_id, snowflake role_id, std::string name, permission permissions, uint32_t rgb_color = 0, bool hoist = false, bool mentionable = false);

      /** Removes a role from a guild.
       *
       * @param guild_id The guild to remove the role from.
       * @param role_id The role to remove from the guild.
       * @return Success status.
       */
      pplx::task<bool> remove_role(connection_state* conn, snowflake guild_id, snowflake role_id);

      /** Get the amount of users that will be pruned if a prune is run on the guild.
       *
       * @param guild_id The guild to check the prune status of.
       * @param days The number of days to send to the prune command.
       * @return The amount of members that will be pruned if pruned with the given amount of days.
       */
      pplx::task<uint32_t> get_prune_count(connection_state* conn, snowflake guild_id, uint32_t days);

      /** Prunes members from a guild.
       *
       * @param guild_id The guild to prune members from.
       * @param days The number of days to send to the prune command.
       * @return The amount of members that were pruned.
       */
      pplx::task<uint32_t> prune(connection_state* conn, snowflake guild_id, uint32_t days);

      /** Lists the voice regions available.
       *
       * @param guild_id The guild to list voice regions from.
       * @return A list of voice regions.
       */
      pplx::task<std::vector<voice_region>> get_voice_regions(connection_state* conn, snowflake guild_id);

      /** Lists the invites to this guild.
       *
       * @param guild_id The guild to list invites from.
       * @return A list of invites to this guild.
       */
      //  TODO: Implement
      //pplx::task<std::vector<invite>> get_invites(connection_state* conn, snowflake guild_id);

      /** Lists the integrations this guild owns.
       *
       * @param guild_id The guild to list integrations from.
       * @return A list of integrations that this guild owns.
       */
      pplx::task<std::vector<integration>> get_integrations(connection_state* conn, snowflake guild_id);

      /** Attaches an integration object to a guild.
       *
       * @param guild_id The guild to create an integration in.
       * @param type The type of the integration.
       * @param integration_id The integration to attach.
       * @return Success status.
       */
      pplx::task<bool> create_integration(connection_state* conn, snowflake guild_id, std::string type, snowflake integration_id);

      /** Modifies the behavior of an integration.
       *
       * @param guild_id The guild that owns the integration.
       * @param integration_id The integration to modify.
       * @param expire_behavior The behavior when an integration subscription lapses.
       * @param expire_grace_period The period in seconds where the integration will ignore lapsed subscriptions.
       * @param enable_emoticons Whether emoticons should be synced.
       * @return Success status.
       */
      pplx::task<bool> modify_integration(connection_state* conn, snowflake guild_id, snowflake integration_id, uint32_t expire_behavior, uint32_t expire_grace_period, bool enable_emoticons);

      /** Removes an integration from a guild.
       *
       * @param guild_id The guild that the integration should be removed from.
       * @param integration_id The integration to remove.
       */
      pplx::task<bool> remove_integration(connection_state* conn, snowflake guild_id, snowflake integration_id);

      /** Syncs an integration.
       *
       * @param guild_id The guild that owns the integration.
       * @param integration_id The integration to sync.
       */
      pplx::task<bool> sync_integration(connection_state* conn, snowflake guild_id, snowflake integration_id);

      /** Gets an embed for the guild.
       *
       * @param guild_id The guild to get the embed for.
       * @return The embed for the guild.
       */
      //  TODO: Implement
      //guild_embed get_embed(connection_state* conn, snowflake guild_id);

      /** Modifies a guild embed.
       *
       * @param guild_id The guild whose embed should be modified.
       * @param enabled Whether or not the embed should be enabled.
       * @param channel_id The embed channel id.
       * @return The modified guild embed.
       */
      //  TODO: Implement
      //guild_embed modify_embed(connection_state* conn, snowflake guild_id, bool enabled = false, snowflake channel_id = 0);
    }
  }
}
