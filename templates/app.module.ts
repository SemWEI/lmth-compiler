import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
${IMPORT_COMPONENTS}
${IMPORT_SERVICES}

@NgModule({
  declarations: [
    AppComponent,
    ${DECLARATIONS}
  ],
  imports: [
    BrowserModule,
    HttpClientModule,
    AppRoutingModule
  ],
  providers: [
    ${PROVIDERS}
  ],
  bootstrap: [AppComponent]
})
export class AppModule { }
