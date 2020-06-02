<?php

/**
 * Implements hook_views_plugins_alter().
 */
function views_parity_row_views_plugins_alter(&$plugins) {
  foreach ($plugins['row'] as $plugin_name => $plugin) {
    if (!empty($plugin['base']) && strpos($plugin_name, 'rss') === FALSE) {
      $new_plugin = $plugin;
      $new_plugin['title'] .= t(' (alternate)');
      $new_plugin['help'] = t('Display the entity with standard entity view and alternate view mode according to the row index.');
      $new_plugin['handler'] = 'views_parity_row_views_plugin_row_entity_view';
      $new_plugin['path'] = drupal_get_path('module', 'views_parity_row') . '/views';
      $plugins['row'][$plugin_name . '_alternate'] = $new_plugin;
    }
  }
  dpm($plugins);
}
