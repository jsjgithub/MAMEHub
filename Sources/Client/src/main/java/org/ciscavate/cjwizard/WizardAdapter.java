/**
 * Copyright 2008  Eugene Creswick
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package org.ciscavate.cjwizard;

import java.util.List;

/**
 * A convenience class for implemeting parts of the WizardListener interface.
 * 
 * @author rcreswick
 */
public class WizardAdapter implements WizardListener {

  /*
   * (non-Javadoc)
   * 
   * @see org.ciscavate.cjwizard.WizardListener#onCanceled(java.util.List,
   * org.ciscavate.cjwizard.WizardSettings)
   */
  @Override
  public void onCanceled(List<WizardPage> path, WizardSettings settings) {
    // empty implementation.
  }

  /*
   * (non-Javadoc)
   * 
   * @see org.ciscavate.cjwizard.WizardListener#onFinished(java.util.List,
   * org.ciscavate.cjwizard.WizardSettings)
   */
  @Override
  public void onFinished(List<WizardPage> path, WizardSettings settings) {
    // empty implementation.
  }

  /*
   * (non-Javadoc)
   * 
   * @see
   * org.ciscavate.cjwizard.WizardListener#onPageChanged(org.ciscavate.cjwizard
   * .WizardPage, java.util.List)
   */
  @Override
  public void onPageChanged(WizardPage newPage, List<WizardPage> path) {
    // empty implementation.
  }

}
